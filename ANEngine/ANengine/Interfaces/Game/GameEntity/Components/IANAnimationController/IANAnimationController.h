#pragma once

class IANAnimationController
{
protected:
	float m_flAnimationDuration;

	ANAnimationComposition m_CurrentAnimationComposition;
	ANAnimationComposition m_PrevAnimationComposition;
	int m_iCurrentAnimationCompositionFrame;

	bool m_bIsCurrentFrameAnimationUpdated;
	float m_flAnimationTime;
	float m_flCurrentRenderTime;

	bool m_bIsOccluded;
public:
	virtual void SetAnimationDuration(float flDuration) = 0;
	virtual bool IsNeedUpdateAnimation(IANApi* pApi) = 0;
	virtual void SetVisible(bool IsVisible) = 0;
	virtual void SetAnimationComposition(ANAnimationComposition AnimationComposition) = 0;
	virtual void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) = 0;
};