#include "../../ANEngine.h"

int ANEntity::GetEntityID()
{
	return this->m_iID;
}

char* ANEntity::GetEntityClassID()
{
	return this->m_szEntityClassID;
}

void ANEntity::SetOrigin(anVec2 Origin)
{
	this->m_vecOrigin = Origin;
}

anVec2 ANEntity::MovePoint(IANApi* pApi, float Speed, anVec2 Origin)
{
	anVec2 Way(Speed * pApi->Frametime);

	if (this->m_vecOrigin.x > Origin.x)
		Way.x = -Way.x;

	if (this->m_vecOrigin.y > Origin.y)
		Way.y = -Way.y;

	auto DifferenceFromCenter = this->m_vecOrigin - Origin;

	if (DifferenceFromCenter.x > 0.f ? DifferenceFromCenter.x + Way.x < 0.f : DifferenceFromCenter.x + Way.x > 0.f)
		this->m_vecOrigin.x = Origin.x;

	if (DifferenceFromCenter.y > 0.f ? DifferenceFromCenter.y + Way.y < 0.f : DifferenceFromCenter.y + Way.y > 0.f)
		this->m_vecOrigin.y = Origin.y;

	if (this->m_vecOrigin.x != Origin.x)
		this->m_vecOrigin.x += Way.x;

	if (this->m_vecOrigin.y != Origin.y)
		this->m_vecOrigin.y += Way.y;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointLeft(IANApi* pApi, float Speed, float XValue)
{
	if (this->m_vecOrigin.x > XValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.x -= Way;

		auto DifferenceFromCenter = this->m_vecOrigin.x - XValue;

		if (DifferenceFromCenter > 0.f && DifferenceFromCenter - Way < 0.f)
			this->m_vecOrigin.x = XValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointRight(IANApi* pApi, float Speed, float XValue)
{
	if (this->m_vecOrigin.x < XValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.x += Way;

		auto DifferenceFromCenter = this->m_vecOrigin.x - XValue;

		if (DifferenceFromCenter < 0.f && DifferenceFromCenter + Way > 0.f)
			this->m_vecOrigin.x = XValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointUp(IANApi* pApi, float Speed, float YValue)
{
	if (this->m_vecOrigin.y > YValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.y -= Way;

		auto DifferenceFromCenter = this->m_vecOrigin.y - YValue;

		if (DifferenceFromCenter > 0.f && DifferenceFromCenter - Way < 0.f)
			this->m_vecOrigin.y = YValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointDown(IANApi* pApi, float Speed, float YValue)
{
	if (this->m_vecOrigin.y < YValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.y += Way;

		auto DifferenceFromCenter = this->m_vecOrigin.y - YValue;

		if (DifferenceFromCenter < 0.f && DifferenceFromCenter + Way > 0.f)
			this->m_vecOrigin.y = YValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveHorizontal(IANApi* pApi, float Speed, float XValue)
{
	auto Way = Speed * pApi->Frametime;

	if (this->m_vecOrigin.x > XValue)
		Way = -Way;

	auto DifferenceFromCenter = this->m_vecOrigin.x - XValue;

	if (DifferenceFromCenter > 0.f ? DifferenceFromCenter + Way < 0.f : DifferenceFromCenter + Way > 0.f)
		this->m_vecOrigin.x = XValue;

	if (this->m_vecOrigin.x != XValue)
		this->m_vecOrigin.x += Way;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveVertical(IANApi* pApi, float Speed, float YValue)
{
	auto Way = Speed * pApi->Frametime;

	if (this->m_vecOrigin.y > YValue)
		Way = -Way;

	auto DifferenceFromCenter = this->m_vecOrigin - YValue;

	if (DifferenceFromCenter.y > 0.f ? DifferenceFromCenter.y + Way < 0.f : DifferenceFromCenter.y + Way > 0.f)
		this->m_vecOrigin.y = YValue;

	if (this->m_vecOrigin.y != YValue)
		this->m_vecOrigin.y += Way;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveLeft(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.x -= Speed * pApi->Frametime;
	
	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveRight(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.x += Speed * pApi->Frametime;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveUp(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.y -= Speed * pApi->Frametime;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveDown(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.y += Speed * pApi->Frametime;

	return this->m_vecOrigin;
}

anVec2 ANEntity::GetOrigin()
{
	return this->m_vecOrigin;
}

void ANEntity::SetVisible(bool IsVisible)
{
	this->m_bIsOccluded = !IsVisible;
}

bool ANEntity::GetVisible()
{
	return !this->m_bIsOccluded;
}

void ANEntity::SetEntitySize(anVec2 EntitySize)
{
	this->m_vecEntitySize = EntitySize;
}

anVec2 ANEntity::GetEntitySize()
{
	return this->m_vecEntitySize;
}

anVec2 ANEntity::CalcEntitySize(IANApi* pApi)
{
	anVec2 FrameSize = this->m_vecEntitySize;

	if (!FrameSize)
	{
		if (auto AnimationCompositionFrame = this->m_pAnimCompositionController->GetCurrentAnimationCompositionFrame(pApi))
			FrameSize = pApi->GetImageSize(AnimationCompositionFrame);
	}

	return FrameSize;
}

anRect ANEntity::CalcBBox(IANApi* pApi)
{
	return ANMathUtils::CalcBBox(this->m_vecOrigin, CalcEntitySize(pApi));
}

anRect ANEntity::CalcScreenBBox(IANApi* pApi, IANWorld* pWorld)
{
	return ANMathUtils::CalcScreenBBox(pWorld->GetMetrics(), this->m_vecOrigin, CalcEntitySize(pApi));
}

void ANEntity::DrawRectRegion(IANApi* pApi, IANWorld* pWorld, anColor Color)
{
	auto FrameSize = CalcEntitySize(pApi);

	if (!FrameSize)
		return;

	auto ScreenBBox = ANMathUtils::CalcScreenBBox(pWorld->GetMetrics(), this->m_vecOrigin, FrameSize);

	pApi->DrawRectangle(ScreenBBox.first, ScreenBBox.GetPointsDistantion(), Color, 3.f);
}

void ANEntity::DrawFromComposition(IANApi* pApi, IANWorld* pWorld)
{
	auto AnimationCompositionFrame = this->m_pAnimCompositionController->GetCurrentAnimationCompositionFrame(pApi);

	if (!AnimationCompositionFrame)
		return;

	if (this->m_bIsOccluded)
		return;

	auto Screen = ANMathUtils::CalcScreenBBox(pWorld->GetMetrics(), this->m_vecOrigin, !this->m_vecEntitySize ? pApi->GetImageSize(AnimationCompositionFrame) : this->m_vecEntitySize);

	pApi->DrawImage(
		AnimationCompositionFrame,
		Screen.first,
		Screen.GetPointsDistantion(),
		1.f);
}

bool ANEntity::IsWorldPointIntersected(IANApi* pApi, anVec2 WorldPoint)
{
	return ANMathUtils::CalcBBox(this->m_vecOrigin, CalcEntitySize(pApi)).IsIntersected(WorldPoint);
}

bool ANEntity::IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint)
{
	return ANMathUtils::CalcScreenBBox(pWorld->GetMetrics(), this->m_vecOrigin, CalcEntitySize(pApi)).IsIntersected(ScreenPoint);
}

void ANEntity::SetInteractionController(IANInteractionController* pIANInteractionController)
{
	this->m_pIANInteractionControllerUserCallback = pIANInteractionController;
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

IANAnimationCompositionController* ANEntity::GetAnimCompositionController()
{
	return this->m_pAnimCompositionController;
}

IANEntity& ANEntity::Update(IANApi* pApi)
{
	if (this->m_pIANInteractionControllerUserCallback != nullptr)
	{
		auto iml = (ANInteractionMessagesList*)pApi->GetInteractionMessagesList();

		if (iml->m_InteractionMessagesList.size() != 0)
		{
			iml->LockList();

			for (auto it = iml->m_InteractionMessagesList.begin(); it < iml->m_InteractionMessagesList.end(); it++)
			{
				auto& interactionMessage = *it;

				if ((interactionMessage.m_pszEntityName == nullptr && interactionMessage.m_pszEntityClassIDName == nullptr)
					|| (this->m_szEntityName != nullptr && interactionMessage.m_pszEntityName != nullptr && !strcmp(interactionMessage.m_pszEntityName, this->m_szEntityName))
					|| (this->m_szEntityClassID != nullptr && interactionMessage.m_pszEntityClassIDName != nullptr && !strcmp(interactionMessage.m_pszEntityClassIDName, this->m_szEntityClassID)))
				{
					if (interactionMessage.m_pRemoteEntity != nullptr && *interactionMessage.m_pRemoteEntity != nullptr)
					{
						if (this->m_pIANInteractionControllerUserCallback->ActionHandler(
							pApi,
							interactionMessage.m_pszEventClassID,
							interactionMessage.m_pszEventMessage,
							this,
							interactionMessage.m_pRemoteEntity,
							interactionMessage.m_pReversedUserData,
							interactionMessage.m_bNeedCancelEvent))
						{
							it = iml->m_InteractionMessagesList.erase(it);

							if (it == iml->m_InteractionMessagesList.end())
								break;

							continue;
						}
					}
				}
			}

			iml->UnlockList();
		}
	}

	return *this;
}

void ANEntity::SetUserDataPointer(void* pUserData)
{
	this->m_pUserData = pUserData;
}

void* ANEntity::GetUserDataPointer()
{
	return this->m_pUserData;
}
