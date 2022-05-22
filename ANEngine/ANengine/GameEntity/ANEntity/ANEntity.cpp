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

void ANEntity::SetVisible(bool IsVisible)
{
	this->m_bIsOccluded = IsVisible;
}

void ANEntity::DrawFromComposition(IANApi* pApi, IANWorld* pWorld)
{
	if (this->m_bIsOccluded)
		return;

	auto AnimationCompositionFrame = this->m_pIANAnimationCompositionController->GetCurrentAnimationCompositionFrame(pApi);

	if (!AnimationCompositionFrame)
		return;

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

