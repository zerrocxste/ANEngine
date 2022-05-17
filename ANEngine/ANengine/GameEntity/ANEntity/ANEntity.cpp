#include "../../ANEngine.h"

int ANEntity::GetEntityID()
{
	return this->m_ID;
}

char* ANEntity::GetEntityClassID()
{
	return this->m_szEntityClassID;
}

void ANEntity::SetOrigin(anVec2 Origin)
{
	this->m_Origin = Origin;
}

void ANEntity::MovePoint(IANApi* pApi, float Speed, anVec2 Origin)
{
	this->m_Origin += Origin * (Speed * pApi->Frametime);
}

void ANEntity::MoveLeft(IANApi* pApi, float Speed)
{
	this->m_Origin.x -= Speed * pApi->Frametime;
}

void ANEntity::MoveRight(IANApi* pApi, float Speed)
{
	this->m_Origin.x += Speed * pApi->Frametime;
}

void ANEntity::MoveUp(IANApi* pApi, float Speed)
{
	this->m_Origin.y -= Speed * pApi->Frametime;
}

void ANEntity::MoveDown(IANApi* pApi, float Speed)
{
	this->m_Origin.y += Speed * pApi->Frametime;
}

anVec2 ANEntity::GetOrigin()
{
	return this->m_Origin;
}

void ANEntity::SetAnimationDuration(float flDuration)
{
	this->m_flAnimationDuration = flDuration;
}

bool ANEntity::IsNeedUpdateAnimation(IANApi* pApi)
{
	if (!this->m_flAnimationDuration)
		return false;

	if (this->m_flCurrentRenderTime == pApi->TotalRenderTime)
		return this->m_bIsCurrentFrameAnimationUpdated;

	this->m_flCurrentRenderTime = pApi->TotalRenderTime;

	this->m_bIsCurrentFrameAnimationUpdated = this->m_flAnimationTime <= 0.f;

	if (this->m_bIsCurrentFrameAnimationUpdated)
		this->m_flAnimationTime = this->m_flAnimationDuration;

	this->m_flAnimationTime -= pApi->Frametime;

	return this->m_bIsCurrentFrameAnimationUpdated;
}

void ANEntity::SetVisible(bool IsVisible)
{
	this->m_bIsOccluded = IsVisible;
}

void ANEntity::SetAnimationComposition(ANAnimationComposition AnimationComposition)
{
	this->m_CurrentAnimationComposition = AnimationComposition;
}

void ANEntity::DrawFromComposition(IANApi* pApi, IANWorld* pWorld)
{
	if (!this->m_CurrentAnimationComposition)
		return;

	if (this->m_bIsOccluded)
		return;

	if (this->m_PrevAnimationComposition != this->m_CurrentAnimationComposition || this->m_iCurrentAnimationCompositionFrame >= *(int*)this->m_CurrentAnimationComposition)
		this->m_iCurrentAnimationCompositionFrame = 0;

	auto AnimationCompositionFrame = (ANImageID)((ANAnimationComposition)((std::uintptr_t)this->m_CurrentAnimationComposition + sizeof(int)))[this->m_iCurrentAnimationCompositionFrame];

	this->m_PrevAnimationComposition = this->m_CurrentAnimationComposition;

	if (IsNeedUpdateAnimation(pApi))
		this->m_iCurrentAnimationCompositionFrame++;

	auto FrameSize = pApi->GetImageSize(AnimationCompositionFrame);

	auto wm = pWorld->GetMetrics();

	auto ScreenPos = ANMathUtils::WorldToScreen(wm.m_WorldSize, wm.m_WorldScreenPos, wm.m_WorldScreenSize, wm.m_CameraWorld, this->m_Origin);
	FrameSize = ANMathUtils::WorldToScreen(wm.m_WorldSize, wm.m_WorldScreenPos, wm.m_WorldScreenSize, wm.m_CameraWorld, this->m_Origin + FrameSize) - ScreenPos;

	ScreenPos.x -= (FrameSize.x * 0.5f);
	ScreenPos.y -= FrameSize.y;

	pApi->DrawImage(
		AnimationCompositionFrame,
		ScreenPos,
		FrameSize,
		1.f);
}

void ANEntity::SetEntityName(const char* szEntityName)
{
	auto LengthEntityName = strlen(szEntityName) + 1;
	memcpy(this->m_szEntityName = new char[LengthEntityName], szEntityName, LengthEntityName);
}

char* ANEntity::GetEntityName()
{
	return this->m_szEntityName;
}

