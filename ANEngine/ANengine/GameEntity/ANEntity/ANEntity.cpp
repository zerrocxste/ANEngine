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
	anVec2 Way(Speed * pApi->Frametime);

	if (this->m_Origin.x > Origin.x)
		Way.x = -Way.y;

	if (this->m_Origin.y > Origin.y)
		Way.y = -Way.y;

	auto DifferenceFromCenter = this->m_Origin - Origin;

	if (DifferenceFromCenter.x > 0.f ? DifferenceFromCenter.x + Way.x < 0.f : DifferenceFromCenter.x + Way.x > 0.f)
		this->m_Origin.x = Origin.x;

	if (DifferenceFromCenter.y > 0.f ? DifferenceFromCenter.y + Way.y < 0.f : DifferenceFromCenter.y + Way.y > 0.f)
		this->m_Origin.y = Origin.y;

	if (this->m_Origin.x != Origin.x)
		this->m_Origin.x += Way.x;

	if (this->m_Origin.y != Origin.y)
		this->m_Origin.y += Way.y;
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

void ANEntity::SetEntitySize(anVec2 EntitySize)
{
	this->m_EntitySize = EntitySize;
}

void ANEntity::DrawFromComposition(IANApi* pApi, IANWorld* pWorld)
{
	if (this->m_bIsOccluded)
		return;

	auto AnimationCompositionFrame = this->m_pIANAnimationCompositionController->GetCurrentAnimationCompositionFrame(pApi);

	if (!AnimationCompositionFrame)
		return;

	auto FrameSize = !this->m_EntitySize ? pApi->GetImageSize(AnimationCompositionFrame) : this->m_EntitySize;

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

bool ANEntity::IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint)
{
	auto ScreenPointActor = pApi->WorldToScreen(pWorld, this->m_Origin);

	auto CustomFrameSizeInvalid = !this->m_EntitySize;

	anVec2 FrameSize;

	if (CustomFrameSizeInvalid)
	{
		auto AnimationCompositionFrame = this->m_pIANAnimationCompositionController->GetCurrentAnimationCompositionFrame(pApi);

		if (!AnimationCompositionFrame)
			return false;

		FrameSize = pApi->GetImageSize(AnimationCompositionFrame);
	}
	else
		FrameSize = this->m_EntitySize;

	auto wm = pWorld->GetMetrics();

	FrameSize = ANMathUtils::WorldToScreen(wm.m_WorldSize, wm.m_WorldScreenPos, wm.m_WorldScreenSize, wm.m_CameraWorld, this->m_Origin + FrameSize) - ScreenPointActor;

	ScreenPointActor.x -= (FrameSize.x * 0.5f);
	ScreenPointActor.y -= FrameSize.y;

	return anRect(ScreenPointActor, ScreenPointActor + FrameSize).IsIntersected(ScreenPoint);
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

