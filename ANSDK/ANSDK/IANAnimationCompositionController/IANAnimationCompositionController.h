#pragma once

class IANAnimationCompositionController
{
protected:
	float m_flNewAnimationDuration;
	float m_flAnimationDuration;

	ANAnimationComposition m_CurrentAnimationComposition;
	ANAnimationComposition m_PrevAnimationComposition;
	int m_iCurrentAnimationCompositionFrameCount;

	bool m_bIsCurrentFrameAnimationUpdated;
	float m_flAnimationTime;
	double m_lflCurrentRenderTime;
public:
	virtual void SetAnimationDuration(float flDuration) = 0;
	virtual bool IsNeedUpdateAnimation(IANApi* pApi) = 0;
	virtual void SetAnimationComposition(ANAnimationComposition AnimationComposition) = 0;
	virtual ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) = 0;
	virtual int GetCurrentAnimationCompositionCount() = 0;
};