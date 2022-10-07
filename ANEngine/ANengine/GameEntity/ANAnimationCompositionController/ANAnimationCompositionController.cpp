#include "../../ANEngine.h"

void ANAnimationCompositionController::SetAnimationDuration(float flDuration)
{
	this->m_flNewAnimationDuration = flDuration;
}

void ANAnimationCompositionController::SetAnimationMode(bool bReversePlay)
{
	this->m_bIsPlayInversed = bReversePlay;

	this->m_iCurrentAnimationCompositionFrameCount = this->m_bIsPlayInversed ? (this->m_iCurrentCompositionMaxFrame - 1) : 0;
}

int ANAnimationCompositionController::GetNeedUpdateAnimationCounter(IANApi* pApi)
{
	if (this->m_flNewAnimationDuration <= 0.f)
	{
		this->m_lflCurrentRenderTime = pApi->TotalRenderTime;
		return 0;
	}

	if (this->m_lflCurrentRenderTime == pApi->TotalRenderTime)
		return 0;

	this->m_lflCurrentRenderTime = pApi->TotalRenderTime;

	auto bIsNewAnimationDuration = this->m_flAnimationDuration != this->m_flNewAnimationDuration;

	this->m_flAnimationDuration = this->m_flNewAnimationDuration;

	if (this->m_flAnimationTime <= 0.f || bIsNewAnimationDuration)
		this->m_flAnimationTime = this->m_flAnimationDuration;

	this->m_flAnimationTime -= pApi->Frametime;

	auto iAnimationStep = 0;

	if (this->m_flAnimationTime <= 0.f)
	{
		auto AnimationTimeInversed = -this->m_flAnimationTime + this->m_flAnimationDuration;

		while (AnimationTimeInversed >= this->m_flAnimationDuration)
		{
			iAnimationStep++;
			AnimationTimeInversed -= this->m_flAnimationDuration;
		}
	}

	return iAnimationStep;
}

void ANAnimationCompositionController::SetAnimationComposition(ANAnimationComposition AnimationComposition, bool bClearNextAnimationCycleComplete)
{
	this->m_bNewAnimationCompositionProcessed = !bClearNextAnimationCycleComplete;
	this->m_CurrentAnimationComposition = AnimationComposition;
}

ANImageID ANAnimationCompositionController::GetCurrentAnimationCompositionFrame(IANApi* pApi)
{
	bool IsPlayingComposition = false;

	auto ViewedComposition = this->m_CurrentAnimationComposition;

	if (this->m_PlayingAnimationComposition != 0 && this->m_iCountOfIterationsPlayingComposition > 0)
	{
		ViewedComposition = this->m_PlayingAnimationComposition;
		IsPlayingComposition = true;
	}

	if (!ViewedComposition)
	{
		this->m_PrevAnimationComposition = ANAnimationComposition(0);
		return ANImageID(0);
	}

	this->m_iCurrentCompositionMaxFrame = *(int*)ViewedComposition;

	auto PrevAnimNotSame = this->m_PrevAnimationComposition != ViewedComposition;
	auto CounterIsOut = this->m_bIsPlayInversed ? this->m_iCurrentAnimationCompositionFrameCount < 0 : this->m_iCurrentAnimationCompositionFrameCount >= this->m_iCurrentCompositionMaxFrame;

	if (this->m_lflCurrentRenderTime == pApi->TotalRenderTime)
		this->m_bAnimationCycleOnThisFrameIsComplete = CounterIsOut && !PrevAnimNotSame;

	if (IsPlayingComposition && (CounterIsOut || (this->m_iMaxFramesOfCompositionInIteration > 0 && this->m_iCurrentAnimationCompositionFrameCount >= this->m_iMaxFramesOfCompositionInIteration)))
		this->m_iCountOfIterationsPlayingComposition--;

	if (PrevAnimNotSame || CounterIsOut)
		this->m_iCurrentAnimationCompositionFrameCount = this->m_bIsPlayInversed ? (this->m_iCurrentCompositionMaxFrame - 1) : 0;

	auto AnimationCompositionFrame = (ANImageID)((ANAnimationComposition)((std::uintptr_t)ViewedComposition + sizeof(int)))[this->m_iCurrentAnimationCompositionFrameCount];

	this->m_PrevAnimationComposition = ViewedComposition;

	auto NextFrameIncFrameCount = GetNeedUpdateAnimationCounter(pApi);

	while (NextFrameIncFrameCount)
	{
		auto IsOverflowed = this->m_bIsPlayInversed ? this->m_iCurrentAnimationCompositionFrameCount < 0 : this->m_iCurrentAnimationCompositionFrameCount >= this->m_iCurrentCompositionMaxFrame;

		if (!IsOverflowed)
			this->m_iCurrentAnimationCompositionFrameCount += this->m_bIsPlayInversed ? -1 : 1;
		else
			this->m_iCurrentAnimationCompositionFrameCount = this->m_bIsPlayInversed ? (this->m_iCurrentCompositionMaxFrame - 1) : 0;

		NextFrameIncFrameCount--;
	}

	if (IsPlayingComposition && this->m_iCountOfIterationsPlayingComposition <= 0)
		StopRunningAnimation();

	this->m_bNewAnimationCompositionProcessed = true;
	
	return AnimationCompositionFrame;
}

int ANAnimationCompositionController::GetCurrentAnimationCompositionCount()
{
	return this->m_iCurrentAnimationCompositionFrameCount;
}

void ANAnimationCompositionController::SetCurrentAnimationCompositionCount(int Count)
{
	this->m_iCurrentAnimationCompositionFrameCount = Count;
}

void ANAnimationCompositionController::PlayAnimation(ANAnimationComposition AnimationComposition, bool bLockState, int iCountOfIterations, int iMaxFramesOfCompositionInIteration)
{
	if (this->m_bLockStatePlayingComposition)
		return;

	this->m_PlayingAnimationComposition = AnimationComposition;
	this->m_iCountOfIterationsPlayingComposition = iCountOfIterations;
	this->m_iMaxFramesOfCompositionInIteration = iMaxFramesOfCompositionInIteration;
	this->m_iCurrentAnimationCompositionFrameCount = 0;
	this->m_bNewAnimationCompositionProcessed = false;
	this->m_bLockStatePlayingComposition = bLockState;
}

void ANAnimationCompositionController::StopRunningAnimation()
{
	this->m_PlayingAnimationComposition = ANAnimationComposition(0);
	this->m_iCountOfIterationsPlayingComposition = 0;
	this->m_iMaxFramesOfCompositionInIteration = 0;
	this->m_iCurrentAnimationCompositionFrameCount = 0;
}

void ANAnimationCompositionController::UnlockPlayingAnimationState()
{
	this->m_bLockStatePlayingComposition = false;
}

bool ANAnimationCompositionController::IsAnimationCycleComplete()
{
	return this->m_bAnimationCycleOnThisFrameIsComplete && this->m_bNewAnimationCompositionProcessed;
}