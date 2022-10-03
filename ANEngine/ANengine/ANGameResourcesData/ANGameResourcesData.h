#pragma once

class ANGameResourcesData : public IANError
{
private:
	ANCore* m_pCore;

	std::vector<ANImageID*> m_vImageResourceData;
	std::vector<ANAnimationComposition*> m_vAnimationCompositionData;
public:
	ANGameResourcesData(ANCore* pCore);

	bool CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition, bool bLinkToDataList);
	void DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition);
	void ClearAnimationComposition(ANAnimationComposition* pAnimationComposition);
	void ClearAnimationCompositionData();

	bool CreateImage(const char* pszPath, ANImageID* pImageID, bool bLinkToDataList);
	void DeleteImage(ANImageID* pImageID);
	void ClearImage(ANImageID* pImageID);
	void ClearImageData();
};