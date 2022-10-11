#pragma once

class ANGameResourcesData : public IANError
{
private:
	ANCore* m_pCore;

	std::vector<ANImageID> m_vImageResourceData;
	std::vector<ANAnimationComposition> m_vAnimationCompositionData;
public:
	ANGameResourcesData(ANCore* pCore);

	bool CreateAnimationComposition(const char** pszAnimationLabelsArr, int iAnimationLabelsArrSize, ANAnimationComposition* pAnimationComposition, bool bLinkToDataList);
	void InsertAnimationFrameTo(ANAnimationComposition AnimationCompositionSource, int iAnimationFrameIdxSource, ANAnimationComposition* pAnimationCompositionDest, int iAnimationFrameDest);
	void DeleteAnimationComposition(ANAnimationComposition* pAnimationComposition);
	void ClearAnimationComposition(ANAnimationComposition AnimationComposition);
	void ClearAnimationCompositionData();

	bool CreateImage(const char* pszPath, ANImageID* pImageID, bool bLinkToDataList);
	void DeleteImage(ANImageID* pImageID);
	void ClearImage(ANImageID ImageID);
	void ClearImageData();
};