#include "../../ANEngine.h"

void ANAnimationCompositionController::SetAnimationDuration(float flDuration)
{
	this->m_flNewAnimationDuration = flDuration;
}

int ANAnimationCompositionController::GetNeedUpdateAnimationCounter(IANApi* pApi)
{
	if (this->m_flNewAnimationDuration <= 0.f)
		return false;

	if (this->m_lflCurrentRenderTime == pApi->TotalRenderTime)
		return false;

	this->m_lflCurrentRenderTime = pApi->TotalRenderTime;

	this->m_flAnimationDuration = this->m_flNewAnimationDuration;

	if (this->m_flAnimationTime <= 0.f || this->m_flAnimationDuration != this->m_flNewAnimationDuration)
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

void ANAnimationCompositionController::SetAnimationComposition(ANAnimationComposition AnimationComposition)
{
	this->m_CurrentAnimationComposition = AnimationComposition;
}

ANImageID ANAnimationCompositionController::GetCurrentAnimationCompositionFrame(IANApi* pApi)
{
	if (!this->m_CurrentAnimationComposition)
		return ANImageID(0);

	if (this->m_PrevAnimationComposition != this->m_CurrentAnimationComposition || this->m_iCurrentAnimationCompositionFrameCount >= *(int*)this->m_CurrentAnimationComposition)
		this->m_iCurrentAnimationCompositionFrameCount = 0;

	auto AnimationCompositionFrame = (ANImageID)((ANAnimationComposition)((std::uintptr_t)this->m_CurrentAnimationComposition + sizeof(int)))[this->m_iCurrentAnimationCompositionFrameCount];

	this->m_PrevAnimationComposition = this->m_CurrentAnimationComposition;

	this->m_iCurrentAnimationCompositionFrameCount += GetNeedUpdateAnimationCounter(pApi);

	return AnimationCompositionFrame;
}

int ANAnimationCompositionController::GetCurrentAnimationCompositionCount()
{
	return this->m_iCurrentAnimationCompositionFrameCount;
}
