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
	if (this->m_pIANInteractionController != nullptr)
	{
		auto iml = pApi->GetInteractionMessagesList();

		for (auto& e : iml->m_InteractionMessagesList)
		{
			if (e.m_pszEntityName == nullptr && e.m_pszClassIDName == nullptr)
				this->m_pIANInteractionController->ActionHandler(e.m_pszEventMessage, e.m_pRemoteEntity);
		}

		if (this->m_szEntityName)
		{
			for (auto& e : iml->GetInteractionFromEntityName(this->m_szEntityName))
			{
				this->m_pIANInteractionController->ActionHandler(e->m_pszEventMessage, e->m_pRemoteEntity);
			}
		}
		
		if (this->m_szEntityClassID)
		{
			for (auto& e : iml->GetInteractionFromEntityClassID(this->m_szEntityClassID))
			{
				this->m_pIANInteractionController->ActionHandler(e->m_pszEventMessage, e->m_pRemoteEntity);
			}
		}
	}

	if (this->m_bIsOccluded)
		return;

	auto AnimationCompositionFrame = this->m_pIANAnimationCompositionController->GetCurrentAnimationCompositionFrame(pApi);

	if (!AnimationCompositionFrame)
		return;

	auto Screen = ANMathUtils::CalcBBox(pWorld->GetMetrics(), this->m_Origin, !this->m_EntitySize ? pApi->GetImageSize(AnimationCompositionFrame) : this->m_EntitySize);

	pApi->DrawImage(
		AnimationCompositionFrame,
		Screen.second,
		Screen.first,
		1.f);
}

bool ANEntity::IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint)
{
	anVec2 FrameSize = this->m_EntitySize;

	if (!FrameSize)
	{
		auto AnimationCompositionFrame = this->m_pIANAnimationCompositionController->GetCurrentAnimationCompositionFrame(pApi);

		if (!AnimationCompositionFrame)
			return false;

		FrameSize = pApi->GetImageSize(AnimationCompositionFrame);
	}

	auto Screen = ANMathUtils::CalcBBox(pWorld->GetMetrics(), this->m_Origin, FrameSize);

	return Screen.MakeSwapPoints().MakeSizeToDest().IsIntersected(ScreenPoint);
}

void ANEntity::SetInteractionController(IANInteractionController* pIANInteractionController)
{
	this->m_pIANInteractionController = pIANInteractionController;
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

