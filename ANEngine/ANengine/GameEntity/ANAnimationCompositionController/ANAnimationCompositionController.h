#pragma once

class ANAnimationCompositionController : public IANAnimationCompositionController
{
private:
	bool m_bAnimationCycleOnThisFrameIsComplete;

	bool m_bPrevAnimNotSame;
	bool m_bNewAnimationCompositionProcessed;

	float m_flNewAnimationDuration;
	float m_flAnimationDuration;

	ANAnimationComposition m_CurrentAnimationComposition;
	ANAnimationComposition m_PrevAnimationComposition;
	ANAnimationComposition m_ViewedComposition;
	int m_iCurrentCompositionMaxFrame;

	int m_iCurrentAnimationCompositionFrameCount;

	//IANAnimationCompositionController::PlayAnimation
	bool m_bIsCurrentlyPlayComposition;
	bool m_bLockStatePlayingComposition;
	ANAnimationComposition m_PlayingAnimationComposition;
	int m_iCountOfIterationsPlayingComposition;
	int m_iMaxFramesOfCompositionInIteration;

	float m_flAnimationTime;

	bool m_bIsPlayInversed;

	double m_lflCurrentRenderTime;

	bool m_bIgnoreAnimationBorder;
public:
	void SetAnimationDuration(float flDuration) override;
	void SetAnimationMode(bool bReversePlay) override;
	bool GetAnimationModePlayIsReversed() override;
	int GetNeedUpdateAnimationCounter(IANApi* pApi) override;
	void SetAnimationComposition(ANAnimationComposition AnimationComposition, bool bClearNextAnimationCycleComplete) override;
	ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) override;
	int GetCurrentAnimationCompositionCount() override;
	void SetCurrentAnimationCompositionCount(int Count) override;
	void PlayAnimation(ANAnimationComposition AnimationComposition, bool bLockState, int iCountOfIterations, int iMaxFramesOfCompositionInIteration) override;
	void StopRunningAnimation() override;
	void UnlockPlayingAnimationState() override;
	bool IsAnimationCycleComplete() override;

	bool IsAnimationCounterOut();
	bool AnimationCompositionThink();
};