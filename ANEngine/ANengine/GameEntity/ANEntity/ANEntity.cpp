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

anVec2 ANEntity::MovePoint(IANApi* pApi, float Speed, anVec2 Origin)
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

	return this->m_Origin;
}

anVec2 ANEntity::MoveLeft(IANApi* pApi, float Speed)
{
	this->m_Origin.x -= Speed * pApi->Frametime;
	
	return this->m_Origin;
}

anVec2 ANEntity::MoveRight(IANApi* pApi, float Speed)
{
	this->m_Origin.x += Speed * pApi->Frametime;

	return this->m_Origin;
}

anVec2 ANEntity::MoveUp(IANApi* pApi, float Speed)
{
	this->m_Origin.y -= Speed * pApi->Frametime;

	return this->m_Origin;
}

anVec2 ANEntity::MoveDown(IANApi* pApi, float Speed)
{
	this->m_Origin.y += Speed * pApi->Frametime;

	return this->m_Origin;
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

		for (auto it = iml->m_InteractionMessagesList.begin(); it < iml->m_InteractionMessagesList.end(); it++)
		{
			auto& e = *it;

			if ((e.m_pszEntityName == nullptr && e.m_pszEntityClassIDName == nullptr)
				|| (this->m_szEntityName != nullptr && e.m_pszEntityName != nullptr && !strcmp(e.m_pszEntityName, this->m_szEntityName))
				|| (this->m_szEntityClassID != nullptr && e.m_pszEntityClassIDName != nullptr && !strcmp(e.m_pszEntityClassIDName, this->m_szEntityClassID)))
			{
				if (this->m_pIANInteractionController->ActionHandler(pApi, e.m_pszEventClassID, e.m_pszEventMessage, this, e.m_pRemoteEntity, e.m_pReversedUserData))
					iml->m_InteractionMessagesList.erase(it);
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

