#pragma once

class ANAnimationCompositionController : public IANAnimationCompositionController
{
public:
	void SetAnimationDuration(float flDuration) override;
	int GetNeedUpdateAnimationCounter(IANApi* pApi) override;
	void SetAnimationComposition(ANAnimationComposition AnimationComposition, bool bClearNextAnimationCycleComplete) override;
	ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) override;
	int GetCurrentAnimationCompositionCount() override;
	void PlayAnimation(ANAnimationComposition AnimationComposition, bool bLockState, int iCountOfIterations, int iMaxFramesOfCompositionInIteration) override;
	void StopRunningAnimation() override;
	void UnlockPlayingAnimationState() override;
	bool IsAnimationCycleComplete() override;
};
