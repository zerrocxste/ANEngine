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
		Way.x = -Way.x;

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

anVec2 ANEntity::MovePointLeft(IANApi* pApi, float Speed, float XValue)
{
	if (this->m_Origin.x > XValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_Origin.x -= Way;

		auto DifferenceFromCenter = this->m_Origin.x - XValue;

		if (DifferenceFromCenter > 0.f && DifferenceFromCenter - Way < 0.f)
			this->m_Origin.x = XValue;
	}

	return this->m_Origin;
}

anVec2 ANEntity::MovePointRight(IANApi* pApi, float Speed, float XValue)
{
	if (this->m_Origin.x < XValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_Origin.x += Way;

		auto DifferenceFromCenter = this->m_Origin.x - XValue;

		if (DifferenceFromCenter < 0.f && DifferenceFromCenter + Way > 0.f)
			this->m_Origin.x = XValue;
	}

	return this->m_Origin;
}

anVec2 ANEntity::MovePointUp(IANApi* pApi, float Speed, float YValue)
{
	if (this->m_Origin.y > YValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_Origin.y -= Way;

		auto DifferenceFromCenter = this->m_Origin.y - YValue;

		if (DifferenceFromCenter > 0.f && DifferenceFromCenter - Way < 0.f)
			this->m_Origin.y = YValue;
	}

	return this->m_Origin;
}

anVec2 ANEntity::MovePointDown(IANApi* pApi, float Speed, float YValue)
{
	if (this->m_Origin.y < YValue)
	{
		auto Way = Speed * pApi->Frametime;

		this->m_Origin.y += Way;

		auto DifferenceFromCenter = this->m_Origin.y - YValue;

		if (DifferenceFromCenter < 0.f && DifferenceFromCenter + Way > 0.f)
			this->m_Origin.y = YValue;
	}

	return this->m_Origin;
}

anVec2 ANEntity::MoveHorizontal(IANApi* pApi, float Speed, float XValue)
{
	auto Way = Speed * pApi->Frametime;

	if (this->m_Origin.x > XValue)
		Way = -Way;

	auto DifferenceFromCenter = this->m_Origin.x - XValue;

	if (DifferenceFromCenter > 0.f ? DifferenceFromCenter + Way < 0.f : DifferenceFromCenter + Way > 0.f)
		this->m_Origin.x = XValue;

	if (this->m_Origin.x != XValue)
		this->m_Origin.x += Way;

	return this->m_Origin;
}

anVec2 ANEntity::MoveVertical(IANApi* pApi, float Speed, float YValue)
{
	auto Way = Speed * pApi->Frametime;

	if (this->m_Origin.y > YValue)
		Way = -Way;

	auto DifferenceFromCenter = this->m_Origin - YValue;

	if (DifferenceFromCenter.y > 0.f ? DifferenceFromCenter.y + Way < 0.f : DifferenceFromCenter.y + Way > 0.f)
		this->m_Origin.y = YValue;

	if (this->m_Origin.y != YValue)
		this->m_Origin.y += Way;

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
	this->m_bIsOccluded = !IsVisible;
}

bool ANEntity::GetVisible()
{
	return !this->m_bIsOccluded;
}

void ANEntity::SetEntitySize(anVec2 EntitySize)
{
	this->m_EntitySize = EntitySize;
}

anVec2 ANEntity::GetEntitySize()
{
	return this->m_EntitySize;
}

void ANEntity::DrawFromComposition(IANApi* pApi, IANWorld* pWorld)
{
	auto AnimationCompositionFrame = this->m_pAnimCompositionController->GetCurrentAnimationCompositionFrame(pApi);

	if (!AnimationCompositionFrame)
		return;

	if (this->m_bIsOccluded)
		return;

	auto Screen = ANMathUtils::CalcBBox(pWorld->GetMetrics(), this->m_Origin, !this->m_EntitySize ? pApi->GetImageSize(AnimationCompositionFrame) : this->m_EntitySize);

	pApi->DrawImage(
		AnimationCompositionFrame,
		Screen.first,
		Screen.GetRelativeDistanceBetweenFirstAndSecond(),
		1.f);
}

bool ANEntity::IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint)
{
	anVec2 FrameSize = this->m_EntitySize;

	if (!FrameSize)
	{
		auto AnimationCompositionFrame = this->m_pAnimCompositionController->GetCurrentAnimationCompositionFrame(pApi);

		if (!AnimationCompositionFrame)
			return false;
			
		FrameSize = pApi->GetImageSize(AnimationCompositionFrame);
	}

	return ANMathUtils::CalcBBox(pWorld->GetMetrics(), this->m_Origin, FrameSize).IsIntersected(ScreenPoint);
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

			for (auto it = iml->m_InteractionMessagesList.begin(); it < iml->m_InteractionMessagesList.end(); )
			{
				auto& e = *it;

				if ((e.m_pszEntityName == nullptr && e.m_pszEntityClassIDName == nullptr)
					|| (this->m_szEntityName != nullptr && e.m_pszEntityName != nullptr && !strcmp(e.m_pszEntityName, this->m_szEntityName))
					|| (this->m_szEntityClassID != nullptr && e.m_pszEntityClassIDName != nullptr && !strcmp(e.m_pszEntityClassIDName, this->m_szEntityClassID)))
				{
					if (e.m_pRemoteEntity != nullptr && *e.m_pRemoteEntity != nullptr)
					{
						if (this->m_pIANInteractionControllerUserCallback->ActionHandler(
							pApi,
							e.m_pszEventClassID,
							e.m_pszEventMessage,
							this,
							e.m_pRemoteEntity,
							e.m_pReversedUserData,
							e.m_bNeedCancelEvent))
						{
							it = iml->m_InteractionMessagesList.erase(it);

							if (iml->m_InteractionMessagesList.size() == 0)
								break;

							continue;
						}
					}
				}

				it++;
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
