#pragma once

class ANAnimationCompositionController : public IANAnimationCompositionController
{
private:
	bool m_bAnimationCycleOnThisFrameIsComplete;

	bool m_bPrevAnimNotSame;
	bool m_bNewAnimationCompositionProcessed;

	float m_flNewAnimationDuration;
	float m_flAnimationDuration;

	ANAnimationComposition m_StackAnimationComposition;
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

	double m_lflLastAnimationChangeTime;
	bool m_bIgnoreNextAnimationChangeTimer;

	int m_iRepeatingSameAnimation;

	bool m_bPrintfEnabled;
public:
	void SetAnimationDuration(float flDuration) override;
	void SetAnimationMode(bool bReversePlay) override;
	bool GetAnimationModePlayIsReversed() override;
	int GetNeedUpdateAnimationCounter(IANApi* pApi) override;
	void SetAnimationComposition(IANApi* pApi, ANAnimationComposition AnimationComposition, bool bClearNextAnimationCycleComplete) override;
	ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) override;
	int GetCurrentAnimationCompositionCount() override;
	void SetCurrentAnimationCompositionCount(int Count) override;
	void PlayAnimation(IANApi* pApi, ANAnimationComposition AnimationComposition, bool bLockState, int iCountOfIterations, int iMaxFramesOfCompositionInIteration) override;
	void StopRunningAnimation() override;
	void UnlockPlayingAnimationState() override;
	bool IsAnimationCycleComplete() override;
	void IgnoreNextAnimationChangeTimer() override;
	ANPerfomanceTick GetTimeSinceAnimationChanged(IANApi* pApi) override;
	int GetCounterRepeatingSameAnimation() override;
	void PushAnimationComposition() override;
	void PopAnimationComposition() override;
	void ActivatePrintf(bool activate) override;

	bool IsAnimationCounterOut();
	bool AnimationCompositionThink();
	void UpdateAnimationChangeTimer(IANApi* pApi, bool bSameComposition);
};