#pragma once

class IANAnimationController
{
protected:
	anVec2 m_EntitySize;
	bool m_bIsOccluded;
public:
	virtual void SetVisible(bool IsVisible) = 0;
	virtual void SetEntitySize(anVec2 EntitySize) = 0;
	virtual void PlayAnimation(int iCountOfIterations, int iMaxFramesOfCompositionInIteration) = 0;
	virtual void StopRunningAnimation() = 0;
	virtual void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) = 0;
};