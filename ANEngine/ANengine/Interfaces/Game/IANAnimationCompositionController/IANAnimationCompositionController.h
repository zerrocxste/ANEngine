#pragma once

class IANAnimationCompositionController
{
public:
	virtual void SetAnimationDuration(float flDuration) = 0;
	virtual void SetAnimationMode(bool bReversePlay) = 0;
	virtual int GetNeedUpdateAnimationCounter(IANApi* pApi) = 0;
	virtual void SetAnimationComposition(ANAnimationComposition AnimationComposition, bool bClearNextAnimationCycleComplete = false) = 0;
	virtual ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) = 0;
	virtual int GetCurrentAnimationCompositionCount() = 0;
	virtual void SetCurrentAnimationCompositionCount(int Count) = 0;
	virtual void PlayAnimation(ANAnimationComposition AnimationComposition, bool bLockState = false, int iCountOfIterations = 1, int iMaxFramesOfCompositionInIteration = 0) = 0;
	virtual void StopRunningAnimation() = 0;
	virtual void UnlockPlayingAnimationState() = 0;
	virtual bool IsAnimationCycleComplete() = 0;
};