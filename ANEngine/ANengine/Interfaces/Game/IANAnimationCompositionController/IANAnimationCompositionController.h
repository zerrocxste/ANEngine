#pragma once

class IANAnimationCompositionController
{
protected:
	bool m_bAnimationCycleOnThisFrameIsComplete;

	bool m_bNewAnimationCompositionProcessed;

	float m_flNewAnimationDuration;
	float m_flAnimationDuration;

	ANAnimationComposition m_CurrentAnimationComposition;
	ANAnimationComposition m_PrevAnimationComposition;

	int m_iCurrentAnimationCompositionFrameCount;

	//IANAnimationCompositionController::PlayAnimation
	bool m_bLockStatePlayingComposition;
	ANAnimationComposition m_PlayingAnimationComposition;
	int m_iCountOfIterationsPlayingComposition;
	int m_iMaxFramesOfCompositionInIteration;

	float m_flAnimationTime;

	double m_lflCurrentRenderTime;
public:
	virtual void SetAnimationDuration(float flDuration) = 0;
	virtual int GetNeedUpdateAnimationCounter(IANApi* pApi) = 0;
	virtual void SetAnimationComposition(ANAnimationComposition AnimationComposition, bool bClearNextAnimationCycleComplete = false) = 0;
	virtual ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) = 0;
	virtual int GetCurrentAnimationCompositionCount() = 0;
	virtual void PlayAnimation(ANAnimationComposition AnimationComposition, bool bLockState = false, int iCountOfIterations = 1, int iMaxFramesOfCompositionInIteration = 0) = 0;
	virtual void StopRunningAnimation() = 0;
	virtual void UnlockPlayingAnimationState() = 0;
	virtual bool IsAnimationCycleComplete() = 0;
};