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
	this->m_MoveInfo.m_flSpeed = SPEED_FRAME;

	auto vecCurrentOrigin = this->m_vecOrigin;

	this->m_vecOrigin = Origin;

	if (vecCurrentOrigin.x != this->m_vecOrigin.x)
		this->m_MoveInfo.m_EntityDirectionFlags |= this->m_vecOrigin.x < vecCurrentOrigin.x ? ANDirectionMoveFlags::MOVE_LEFT : ANDirectionMoveFlags::MOVE_RIGHT;

	if (vecCurrentOrigin.y != this->m_vecOrigin.y)
		this->m_MoveInfo.m_EntityDirectionFlags |= this->m_vecOrigin.y < vecCurrentOrigin.y ? ANDirectionMoveFlags::MOVE_UP : ANDirectionMoveFlags::MOVE_DOWN;
}

anVec2 ANEntity::MovePoint(IANApi* pApi, float Speed, anVec2 Origin)
{
	auto vCurrentOrigin = this->m_vecOrigin;

	ANDirectionMoveFlags Flags = MOVE_NO;

	anVec2 vecWay(Speed * pApi->Frametime);

	auto isNeedMoveLeft = this->m_vecOrigin.x > Origin.x;

	Flags |= isNeedMoveLeft ? ANDirectionMoveFlags::MOVE_LEFT : ANDirectionMoveFlags::MOVE_RIGHT;

	if (isNeedMoveLeft)
		vecWay.x = -vecWay.x;

	auto isNeedMoveUp = this->m_vecOrigin.y > Origin.y;

	Flags |= isNeedMoveUp ? ANDirectionMoveFlags::MOVE_UP : ANDirectionMoveFlags::MOVE_DOWN;

	if (isNeedMoveUp)
		vecWay.y = -vecWay.y;

	auto vecDifferenceFromCenter = this->m_vecOrigin - Origin;

	if (vecDifferenceFromCenter.x > 0.f ? vecDifferenceFromCenter.x + vecWay.x < 0.f : vecDifferenceFromCenter.x + vecWay.x > 0.f)
		this->m_vecOrigin.x = Origin.x;
		
	if (vecDifferenceFromCenter.y > 0.f ? vecDifferenceFromCenter.y + vecWay.y < 0.f : vecDifferenceFromCenter.y + vecWay.y > 0.f)
		this->m_vecOrigin.y = Origin.y;
		
	if (this->m_vecOrigin.x != Origin.x)
		this->m_vecOrigin.x += vecWay.x;

	if (this->m_vecOrigin.y != Origin.y)
		this->m_vecOrigin.y += vecWay.y;

	if (this->m_vecOrigin != vCurrentOrigin)
		this->m_MoveInfo.m_EntityDirectionFlags = Flags;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointLeft(IANApi* pApi, float Speed, float XValue)
{
	if (this->m_vecOrigin.x > XValue)
	{
		this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_LEFT;

		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.x -= Way;

		auto flDifferenceFromCenter = this->m_vecOrigin.x - XValue;
		if (flDifferenceFromCenter > 0.f && flDifferenceFromCenter - Way < 0.f)
			this->m_vecOrigin.x = XValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointRight(IANApi* pApi, float Speed, float XValue)
{
	if (this->m_vecOrigin.x < XValue)
	{
		this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_RIGHT;

		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.x += Way;

		auto flDifferenceFromCenter = this->m_vecOrigin.x - XValue;
		if (flDifferenceFromCenter < 0.f && flDifferenceFromCenter + Way > 0.f)
			this->m_vecOrigin.x = XValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointUp(IANApi* pApi, float Speed, float YValue)
{
	if (this->m_vecOrigin.y > YValue)
	{
		this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_UP;

		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.y -= Way;

		auto flDifferenceFromCenter = this->m_vecOrigin.y - YValue;
		if (flDifferenceFromCenter > 0.f && flDifferenceFromCenter - Way < 0.f)
			this->m_vecOrigin.y = YValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MovePointDown(IANApi* pApi, float Speed, float YValue)
{
	if (this->m_vecOrigin.y < YValue)
	{
		this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_DOWN;

		auto Way = Speed * pApi->Frametime;

		this->m_vecOrigin.y += Way;

		auto flDifferenceFromCenter = this->m_vecOrigin.y - YValue;
		if (flDifferenceFromCenter < 0.f && flDifferenceFromCenter + Way > 0.f)
			this->m_vecOrigin.y = YValue;
	}

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveHorizontal(IANApi* pApi, float Speed, float XValue)
{
	auto vCurrentOrigin = this->m_vecOrigin;

	ANDirectionMoveFlags Flags = MOVE_NO;

	auto Way = Speed * pApi->Frametime;

	auto isNeedMoveLeft = this->m_vecOrigin.x > XValue;

	Flags |= isNeedMoveLeft ? ANDirectionMoveFlags::MOVE_LEFT : ANDirectionMoveFlags::MOVE_RIGHT;

	if (isNeedMoveLeft)
		Way = -Way;

	auto flDifferenceFromCenter = this->m_vecOrigin.x - XValue;
	if (flDifferenceFromCenter > 0.f ? flDifferenceFromCenter + Way < 0.f : flDifferenceFromCenter + Way > 0.f)
		this->m_vecOrigin.x = XValue;

	if (this->m_vecOrigin.x != XValue)
		this->m_vecOrigin.x += Way;

	if (this->m_vecOrigin != vCurrentOrigin)
		this->m_MoveInfo.m_EntityDirectionFlags = Flags;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveVertical(IANApi* pApi, float Speed, float YValue)
{
	auto vCurrentOrigin = this->m_vecOrigin;

	ANDirectionMoveFlags Flags = MOVE_NO;

	auto Way = Speed * pApi->Frametime;

	auto isNeedMoveUp = this->m_vecOrigin.y > YValue;

	Flags |= isNeedMoveUp ? ANDirectionMoveFlags::MOVE_UP : ANDirectionMoveFlags::MOVE_DOWN;

	if (isNeedMoveUp)
		Way = -Way;
	
	auto vecDifferenceFromCenter = this->m_vecOrigin - YValue;
	if (vecDifferenceFromCenter.y > 0.f ? vecDifferenceFromCenter.y + Way < 0.f : vecDifferenceFromCenter.y + Way > 0.f)
		this->m_vecOrigin.y = YValue;

	if (this->m_vecOrigin.y != YValue)
		this->m_vecOrigin.y += Way;

	if (this->m_vecOrigin != vCurrentOrigin)
		this->m_MoveInfo.m_EntityDirectionFlags = Flags;

	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveLeft(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.x -= Speed * pApi->Frametime;
	this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_LEFT;
	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveRight(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.x += Speed * pApi->Frametime;
	this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_RIGHT;
	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveUp(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.y -= Speed * pApi->Frametime;
	this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_UP;
	return this->m_vecOrigin;
}

anVec2 ANEntity::MoveDown(IANApi* pApi, float Speed)
{
	this->m_vecOrigin.y += Speed * pApi->Frametime;
	this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_DOWN;
	return this->m_vecOrigin;
}

anVec2 ANEntity::GetOrigin()
{
	return this->m_vecOrigin;
}

ANEntityMoveInfo ANEntity::GetMoveInfo()
{
	return this->m_MoveInfo;
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
	this->m_MoveInfo.m_EntityDirectionFlags = ANDirectionMoveFlags::MOVE_NO;
	this->m_MoveInfo.m_flSpeed = 0.f;

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

void ANEntity::SetOnReleaseUserData(fOnReleaseUserData pfOnReleaseUserData)
{
	this->m_pfOnReleaseUserData = pfOnReleaseUserData;
}

void* ANEntity::GetUserDataPointer()
{
	return this->m_pUserData;
}

void ANEntity::CallOnReleaseUserData(void* _this)
{
	if (!this->m_pfOnReleaseUserData)
		return;

	this->m_pfOnReleaseUserData(_this);
}
