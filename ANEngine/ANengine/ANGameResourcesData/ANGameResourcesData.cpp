#include "../ANEngine.h"

ANGameResourcesData::ANGameResourcesData(ANCore* pCore) :
	m_pCore(pCore)
{

}

bool ANGameResourcesData::CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition, bool bLinkToDataList)
{
	if (iAnimationLabelsArrSize == 0)
		return false;

	*pAnimationComposition = (ANAnimationComposition)ANMemory::GetInstance()->ResourceAllocate(sizeof(anFramesLength) + (sizeof(ANCompositionFrame) * iAnimationLabelsArrSize));

	*(anFramesLength*)*pAnimationComposition = iAnimationLabelsArrSize;

	auto ResourceManager = this->m_pCore->GetResourceManager();
	auto Renderer = this->m_pCore->GetRenderer();

	auto AnimationComposition = (ANAnimationComposition)((std::uintptr_t)*pAnimationComposition + sizeof(anFramesLength));

	for (auto i = 0; i < iAnimationLabelsArrSize; i++)
	{
		ANImageID Image = 0;

		ANUniqueResource ImageResource;

		if (!ResourceManager->ReadBinFile(pszAnimationLabelsArr[i], &ImageResource))
		{
			this->SetError(ResourceManager->What());
			return false;
		}

		if (!Renderer->CreateImageFromResource(&ImageResource, &Image))
		{
			this->SetError(Renderer->What());
			return false;
		}

		AnimationComposition[i] = ANCompositionFrame{ true, Image };
	}

	if (bLinkToDataList)
		this->m_vAnimationCompositionData.push_back(*pAnimationComposition);

	return true;
}

void ANGameResourcesData::InsertAnimationFrameTo(ANAnimationComposition AnimationCompositionSource, int iAnimationFrameIdxSource, ANAnimationComposition* pAnimationCompositionDest, int iAnimationFrameDest)
{
	auto iSourceCompositionMaxFrames = *(anFramesLength*)AnimationCompositionSource;

	if (iAnimationFrameIdxSource >= iSourceCompositionMaxFrames)
	{
		this->SetError(__FUNCTION__ ": Invalid source index. Max source animation composition size: %d, index: %d", iSourceCompositionMaxFrames, iAnimationFrameIdxSource);
		return;
	}

	auto iDestCompositionMaxFrames = *(anFramesLength*)(*pAnimationCompositionDest);

	if (iAnimationFrameDest != -1)
	{
		if (iAnimationFrameDest > iDestCompositionMaxFrames)
		{
			this->SetError(__FUNCTION__ ": Invalid dest index. Max dest animation composition size: %d, index: %d", iDestCompositionMaxFrames, iAnimationFrameDest);
			return;
		}
	}

	auto pFrame = ((ANAnimationComposition)((std::uintptr_t)AnimationCompositionSource + sizeof(anFramesLength)))[iAnimationFrameIdxSource];

	auto iMaxByteLengthAnimationCompositionDest = sizeof(anFramesLength) + (iDestCompositionMaxFrames * sizeof(ANCompositionFrame));

	auto pNewAnimationComposition = (ANAnimationComposition)ANMemory::GetInstance()->ResourceAllocate(iMaxByteLengthAnimationCompositionDest + sizeof(ANImageID));

	memcpy(pNewAnimationComposition, *pAnimationCompositionDest, iMaxByteLengthAnimationCompositionDest);

	auto it = std::find(
		this->m_vAnimationCompositionData.begin(),
		this->m_vAnimationCompositionData.end(),
		*pAnimationCompositionDest);

	if (it != this->m_vAnimationCompositionData.end())
		this->m_vAnimationCompositionData.erase(it);

	ANMemory::GetInstance()->FreeResource(*pAnimationCompositionDest);

	if (iAnimationFrameDest == -1)
	{
		((ANAnimationComposition)(((std::uintptr_t)pNewAnimationComposition) + sizeof(anFramesLength)))[iDestCompositionMaxFrames] = ANCompositionFrame{ false, pFrame.m_Frame };
	}
	else
	{
		auto pFramesData = (ANAnimationComposition)(((std::uintptr_t)pNewAnimationComposition) + sizeof(anFramesLength));
		memmove(&pFramesData[iAnimationFrameDest], &pFramesData[iAnimationFrameDest + 1], (iDestCompositionMaxFrames - iAnimationFrameDest) * sizeof(ANAnimationComposition));
		pFramesData[iAnimationFrameDest] = ANCompositionFrame{ false, pFrame.m_Frame };
	}

	*(anFramesLength*)pNewAnimationComposition += 1;

	*pAnimationCompositionDest = pNewAnimationComposition;

	this->m_vAnimationCompositionData.push_back(*pAnimationCompositionDest);
}

void ANGameResourcesData::DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition)
{
	auto it = std::find(this->m_vAnimationCompositionData.begin(), this->m_vAnimationCompositionData.end(), *pAnimationComposition);

	if (it != this->m_vAnimationCompositionData.end())
		this->m_vAnimationCompositionData.erase(it);

	ClearAnimationComposition(*pAnimationComposition);

	*pAnimationComposition = nullptr;
}

void ANGameResourcesData::ClearAnimationComposition(ANAnimationComposition AnimationComposition)
{
	auto iLengthComposition = *(anFramesLength*)AnimationComposition;
	auto AnimationCompositionData = (ANAnimationComposition)((std::uintptr_t)AnimationComposition + sizeof(anFramesLength));

	for (auto i = 0; i < iLengthComposition; i++)
	{
		if (!AnimationCompositionData[i].m_bIsUnique)
			continue;

		this->m_pCore->GetRenderer()->FreeImage(AnimationCompositionData[i].m_Frame);
	}

	ANMemory::GetInstance()->FreeResource(AnimationComposition);
}

void ANGameResourcesData::ClearAnimationCompositionData()
{
	for (auto AnimationComposition : this->m_vAnimationCompositionData)
	{
		ClearAnimationComposition(AnimationComposition);
	}

	this->m_vAnimationCompositionData.clear();
}

bool ANGameResourcesData::CreateImage(const char* pszPath, ANImageID* pImageID, bool bLinkToDataList)
{
	auto ResourceManager = this->m_pCore->GetResourceManager();

	ANUniqueResource ImageResource;

	if (!ResourceManager->ReadBinFile(pszPath, &ImageResource))
	{
		this->SetError(ResourceManager->What());
		return false;
	}

	auto Renderer = this->m_pCore->GetRenderer();

	auto ret = Renderer->CreateImageFromResource(&ImageResource, pImageID);

	if (!ret)
	{
		this->SetError(Renderer->What());
		return false;
	}

	return true;
}

void ANGameResourcesData::DeleteImage(ANImageID* pImageID)
{
	auto it = std::find(this->m_vImageResourceData.begin(), this->m_vImageResourceData.end(), *pImageID);

	if (it != this->m_vImageResourceData.end())
		this->m_vImageResourceData.erase(it);

	ClearImage(*pImageID);

	*pImageID = nullptr;
}

void ANGameResourcesData::ClearImage(ANImageID ImageID)
{
	this->m_pCore->GetRenderer()->FreeImage(ImageID);
}

void ANGameResourcesData::ClearImageData()
{
	for (auto Image : this->m_vImageResourceData)
	{
		ClearImage(Image);
	}

	this->m_vImageResourceData.clear();
}
