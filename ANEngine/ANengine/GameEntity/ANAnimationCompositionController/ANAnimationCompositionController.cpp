#include "../../ANEngine.h"

void ANAnimationCompositionController::SetAnimationDuration(float flDuration)
{
	this->m_flNewAnimationDuration = flDuration;
}

void ANAnimationCompositionController::SetAnimationMode(bool bReversePlay)
{
	if (bReversePlay == this->m_bIsPlayInversed)
		return;

	if (!this->m_bIsPlayInversed)
	{
		if (!this->m_iCurrentAnimationCompositionFrameCount)
			this->m_iCurrentAnimationCompositionFrameCount = this->m_iCurrentCompositionMaxFrame - 1;
	}
	else
	{
		if (this->m_iCurrentAnimationCompositionFrameCount >= (this->m_iCurrentCompositionMaxFrame - 1))
			this->m_iCurrentAnimationCompositionFrameCount = 0;
	}

	this->m_bIsPlayInversed = bReversePlay;
}

bool ANAnimationCompositionController::GetAnimationModePlayIsReversed()
{
	return this->m_bIsPlayInversed;
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

void ANAnimationCompositionController::SetAnimationComposition(IANApi* pApi, ANAnimationComposition AnimationComposition, bool bClearNextAnimationCycleComplete)
{
	ANAnimationComposition PrevComposition = nullptr;

	if (this->m_StackAnimationComposition != nullptr && !this->m_bIgnoreNextAnimationChangeTimer)
	{
		PrevComposition = this->m_StackAnimationComposition;
		PopAnimationComposition();
	}
	else
	{
		PrevComposition = this->m_CurrentAnimationComposition;
	}

	this->m_bNewAnimationCompositionProcessed = !bClearNextAnimationCycleComplete;
	this->m_CurrentAnimationComposition = AnimationComposition;

	if (this->m_bPrintfEnabled)
	{
		printf("%p %p\n", PrevComposition, this->m_CurrentAnimationComposition);
	}

	UpdateAnimationChangeTimer(pApi, PrevComposition == this->m_CurrentAnimationComposition);
}

ANImageID ANAnimationCompositionController::GetCurrentAnimationCompositionFrame(IANApi* pApi)
{
	if (!AnimationCompositionThink())
		return ANImageID(0);

	auto CounterIsOut = IsAnimationCounterOut();

	if (this->m_lflCurrentRenderTime == pApi->TotalRenderTime)
	{
		this->m_bAnimationCycleOnThisFrameIsComplete = CounterIsOut && !this->m_bPrevAnimNotSame;

		/*if (this->m_bAnimationCycleOnThisFrameIsComplete)
			this->m_iRepeatingSameAnimation++;*/
	}

	if (this->m_bIsCurrentlyPlayComposition &&
		(CounterIsOut || (this->m_iMaxFramesOfCompositionInIteration > 0 && this->m_iCurrentAnimationCompositionFrameCount >= this->m_iMaxFramesOfCompositionInIteration))) {
		this->m_iCountOfIterationsPlayingComposition--;
	}
		
	ANCompositionFrame AnimationCompositionFrame{};

	if (this->m_iCurrentCompositionMaxFrame > 0)
	{
		auto clamped = this->m_iCurrentAnimationCompositionFrameCount;

		if (clamped < 0)
			clamped = 0;

		if (clamped >= this->m_iCurrentCompositionMaxFrame)
			clamped = this->m_iCurrentCompositionMaxFrame - 1;

		AnimationCompositionFrame = ((ANAnimationComposition)((std::uintptr_t)this->m_ViewedComposition + sizeof(anFramesLength)))[clamped];
	}
		
	if (this->m_bPrevAnimNotSame || CounterIsOut)
	{
		this->m_iCurrentAnimationCompositionFrameCount = this->m_bIsPlayInversed ? (this->m_iCurrentCompositionMaxFrame - 1) : 0;
		this->m_iRepeatingSameAnimation++;
	}

	auto NextFrameIncFrameCount = GetNeedUpdateAnimationCounter(pApi);

	while (NextFrameIncFrameCount)
	{
		auto IsOverflowed = IsAnimationCounterOut();

		if (!IsOverflowed)
			this->m_iCurrentAnimationCompositionFrameCount += this->m_bIsPlayInversed ? -1 : 1;
		else
		{
			this->m_iRepeatingSameAnimation++;
			this->m_bAnimationCycleOnThisFrameIsComplete = true;
			this->m_iCurrentAnimationCompositionFrameCount = this->m_bIsPlayInversed ? (this->m_iCurrentCompositionMaxFrame - 1) : 0;
		}

		NextFrameIncFrameCount--;
	}
		
	if (this->m_bIsCurrentlyPlayComposition && this->m_iCountOfIterationsPlayingComposition <= 0)
		StopRunningAnimation();

	this->m_bNewAnimationCompositionProcessed = true;
	
	return AnimationCompositionFrame.m_Frame;
}

int ANAnimationCompositionController::GetCurrentAnimationCompositionCount()
{
	return this->m_iCurrentAnimationCompositionFrameCount;
}

void ANAnimationCompositionController::SetCurrentAnimationCompositionCount(int Count)
{
	this->m_iCurrentAnimationCompositionFrameCount = Count;
}

void ANAnimationCompositionController::PlayAnimation(IANApi* pApi, ANAnimationComposition AnimationComposition, bool bLockState, int iCountOfIterations, int iMaxFramesOfCompositionInIteration)
{
	if (this->m_bLockStatePlayingComposition)
		return;

	auto PrevComposition = this->m_PlayingAnimationComposition;
	this->m_PlayingAnimationComposition = AnimationComposition;
	this->m_iCountOfIterationsPlayingComposition = iCountOfIterations;
	this->m_iMaxFramesOfCompositionInIteration = iMaxFramesOfCompositionInIteration;
	this->m_iCurrentAnimationCompositionFrameCount = 0;
	this->m_bNewAnimationCompositionProcessed = false;
	this->m_bLockStatePlayingComposition = bLockState;
	UpdateAnimationChangeTimer(pApi, PrevComposition == this->m_PlayingAnimationComposition);
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

void ANAnimationCompositionController::IgnoreNextAnimationChangeTimer()
{
	this->m_bIgnoreNextAnimationChangeTimer = true;
}

ANPerfomanceTick ANAnimationCompositionController::GetTimeSinceAnimationChanged(IANApi* pApi)
{
	return pApi->TotalRenderTime - this->m_lflLastAnimationChangeTime;
}

int ANAnimationCompositionController::GetCounterRepeatingSameAnimation()
{
	return this->m_iRepeatingSameAnimation;
}

void ANAnimationCompositionController::PushAnimationComposition()
{
	this->m_StackAnimationComposition = this->m_CurrentAnimationComposition;
}

void ANAnimationCompositionController::PopAnimationComposition()
{
	this->m_StackAnimationComposition = nullptr;
}

void ANAnimationCompositionController::ActivatePrintf(bool activate)
{
	this->m_bPrintfEnabled = activate;
}

bool ANAnimationCompositionController::IsAnimationCounterOut()
{
	return this->m_bIsPlayInversed ? 
		this->m_iCurrentAnimationCompositionFrameCount < 0 : 
		this->m_iCurrentAnimationCompositionFrameCount >= this->m_iCurrentCompositionMaxFrame;
}

bool ANAnimationCompositionController::AnimationCompositionThink()
{
	this->m_bIsCurrentlyPlayComposition = false;
	this->m_PrevAnimationComposition = this->m_ViewedComposition;

	auto ViewedComposition = this->m_CurrentAnimationComposition;

	if (this->m_PlayingAnimationComposition != 0 && this->m_iCountOfIterationsPlayingComposition > 0)
	{
		ViewedComposition = this->m_PlayingAnimationComposition;
		this->m_bIsCurrentlyPlayComposition = true;
	}

	if (!ViewedComposition)
	{
		this->m_ViewedComposition = this->m_PrevAnimationComposition = ANAnimationComposition(0);
		this->m_iCurrentCompositionMaxFrame = 0;
		return false;
	}

	this->m_ViewedComposition = ViewedComposition;
	this->m_iCurrentCompositionMaxFrame = *(anFramesLength*)ViewedComposition;
	this->m_bPrevAnimNotSame = this->m_PrevAnimationComposition != this->m_ViewedComposition;

	return true;
}

void ANAnimationCompositionController::UpdateAnimationChangeTimer(IANApi* pApi, bool bSameComposition)
{
	if (this->m_bIgnoreNextAnimationChangeTimer)
	{
		this->m_bIgnoreNextAnimationChangeTimer = false;
		return;
	}

	this->m_lflLastAnimationChangeTime = pApi->TotalRenderTime;

	if (!bSameComposition)
	{
		this->m_iRepeatingSameAnimation = 0;
	}
}