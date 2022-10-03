#include "../ANEngine.h"

ANGameResourcesData::ANGameResourcesData(ANCore* pCore) :
	m_pCore(pCore)
{

}

bool ANGameResourcesData::CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition, bool bLinkToDataList)
{
	if (iAnimationLabelsArrSize == 0)
		return false;

	*pAnimationComposition = (ANAnimationComposition)ANMemory::GetInstance()->ResourceAllocate(sizeof(int) + (sizeof(ANAnimationComposition) * iAnimationLabelsArrSize));

	if (!*pAnimationComposition)
		return false;

	*(int*)*pAnimationComposition = iAnimationLabelsArrSize;

	auto AnimationComposition = (ANAnimationComposition**)((std::uintptr_t)*pAnimationComposition + sizeof(int));

	for (auto i = 0; i < iAnimationLabelsArrSize; i++)
	{
		ANImageID Image = 0;

		ANUniqueResource ImageResource;

		if (!this->m_pCore->GetResourceManager()->ReadBinFile(pszAnimationLabelsArr[i], &ImageResource))
			return false;

		if (!this->m_pCore->GetRenderer()->CreateImageFromResource(&ImageResource, &Image))
			return false;

		AnimationComposition[i] = (ANAnimationComposition*)Image;
	}

	if (bLinkToDataList)
		this->m_vAnimationCompositionData.push_back(pAnimationComposition);

	return true;
}

void ANGameResourcesData::DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition)
{
	auto it = std::find(this->m_vAnimationCompositionData.begin(), this->m_vAnimationCompositionData.end(), pAnimationComposition);

	if (it != this->m_vAnimationCompositionData.end())
		this->m_vAnimationCompositionData.erase(it);

	ClearAnimationComposition(pAnimationComposition);
}

void ANGameResourcesData::ClearAnimationComposition(ANAnimationComposition* pAnimationComposition)
{
	auto AnimationComposition = (ANAnimationComposition**)((std::uintptr_t)*pAnimationComposition + sizeof(int));

	for (auto i = 0; i < *(int*)*pAnimationComposition; i++)
		this->m_pCore->GetRenderer()->FreeImage((ANImageID*)((std::uintptr_t)AnimationComposition + (sizeof(ANAnimationComposition) * i)));

	ANMemory::GetInstance()->FreeResource(*pAnimationComposition);

	*pAnimationComposition = nullptr;
}

void ANGameResourcesData::ClearAnimationCompositionData()
{
	for (auto& pAnimationComposition : this->m_vAnimationCompositionData)
	{
		ClearAnimationComposition(pAnimationComposition);
	}

	this->m_vAnimationCompositionData.clear();
}

bool ANGameResourcesData::CreateImage(const char* pszPath, ANImageID* pImageID, bool bLinkToDataList)
{
	ANUniqueResource ImageResource;

	if (!this->m_pCore->GetResourceManager()->ReadBinFile(pszPath, &ImageResource))
		return false;

	auto ret = this->m_pCore->GetRenderer()->CreateImageFromResource(&ImageResource, pImageID);

	if (bLinkToDataList && ret)
		this->m_vImageResourceData.push_back(pImageID);

	return ret;
}

void ANGameResourcesData::DeleteImage(ANImageID* pImageID)
{
	auto it = std::find(this->m_vImageResourceData.begin(), this->m_vImageResourceData.end(), pImageID);

	if (it != this->m_vImageResourceData.end())
		this->m_vImageResourceData.erase(it);

	ClearImage(pImageID);
}

void ANGameResourcesData::ClearImage(ANImageID* pImageID)
{
	this->m_pCore->GetRenderer()->FreeImage(pImageID);

	pImageID = nullptr;
}

void ANGameResourcesData::ClearImageData()
{
	for (auto pImage : this->m_vImageResourceData)
	{
		ClearImage(pImage);
	}

	this->m_vImageResourceData.clear();
}
