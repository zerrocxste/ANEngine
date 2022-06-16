#include "../../includes.h"

float Step = 250.f;

auto szDoorIntercationClassID = "CLASSID_EVENT_Door";

const char* pszWorld[] = { 
	"house15.bmp" 
};
const char* pszWoody[] = { 
	"w_ms2_0004.png", 
	"w_ms2_0005.png", 
	"w_ms2_0006.png" 
};
const char* pszWoodyLeft[] = { 
	"W_mg3_0000.png", 
	"W_mg3_0001.png", 
	"W_mg3_0002.png", 
	"W_mg3_0003.png", 
	"W_mg3_0004.png", 
	"W_mg3_0005.png", 
	"W_mg3_0006.png", 
	"W_mg3_0007.png" 
};
const char* pszWoodyRight[] = { 
	"W_mg1_0000.png", 
	"W_mg1_0001.png", 
	"W_mg1_0002.png", 
	"W_mg1_0003.png", 
	"W_mg1_0004.png", 
	"W_mg1_0005.png", 
	"W_mg1_0006.png", 
	"W_mg1_0007.png" 
};
const char* pszWoodyDoor[] = { 
	"W_leave_0000.png", 
	"W_leave_0001.png", 
	"W_leave_0002.png", 
	"W_leave_0003.png",
	"W_leave_0004.png", 
	"W_leave_0005.png", 
	"W_leave_0006.png", 
	"W_leave_0007.png", 
	"W_leave_0008.png", 
	"W_leave_0009.png",
};
const char* pszWoodyDoorEnter[] = {
	"W_enter_0015.png",
	"W_enter_0014.png",
	"W_enter_0013.png",
	"W_enter_0012.png",
	"W_enter_0011.png",
	"W_enter_0010.png",
	"W_enter_0009.png",
	"W_enter_0008.png",
	"W_enter_0007.png",
	"W_enter_0006.png",
	"W_enter_0005.png",
	"W_enter_0004.png",
	"W_enter_0003.png",
	"W_enter_0002.png",
	"W_enter_0001.png",
	"W_enter_0000.png",
};
const char* pszDoorAnim[] = { 
	"N_leave_0000.png"
};

DoorEntityInteractionController::DoorEntityInteractionController() 
{
	
}

void DoorEntityInteractionController::ResetDoorState(IANEntity* pThisEntity, IANEntity* pDestEntity, IANEntity* pActorEntity)
{
	pThisEntity->GetAnimCompositionController()->SetAnimationMode(false);
	pThisEntity->GetAnimCompositionController()->UnlockPlayingAnimationState();
	pThisEntity->GetAnimCompositionController()->StopRunningAnimation();
	pDestEntity->GetAnimCompositionController()->SetAnimationMode(false);
	pDestEntity->GetAnimCompositionController()->UnlockPlayingAnimationState();
	pDestEntity->GetAnimCompositionController()->StopRunningAnimation();
	pActorEntity->SetVisible(true);
}

bool DoorEntityInteractionController::ActionHandler(IANApi* pApi, 
	const char* pszEventClassID, 
	const char* pszEventMessage, 
	IANEntity* pThisEntity, 
	IANEntity** ppRemoteEntity, 
	void* pReversedUserData, 
	bool bNeedCancelEvent)
{
	auto pTestLevel = (CTestLevel*)pReversedUserData;

	if (!strcmp(pszEventClassID, szDoorIntercationClassID))
	{
		if (!pApi->GetInteractionMessagesList()->IsEventCanceledByClassID("CLASSID_EVENT_Door", pThisEntity))
			return false;

		auto& pActorEntity = *ppRemoteEntity;

		IANEntity* pDestEntity = nullptr;

		if (!strcmp(pszEventMessage, "EVENT_DoorTransitionHallwayKitchen"))
			pDestEntity = pTestLevel->m_pDoorEntityKitchenHallway;
		else if (!strcmp(pszEventMessage, "EVENT_DoorTransitionKitchenHallway"))
			pDestEntity = pTestLevel->m_pDoorEntityHallwayKitchen;
		else if (!strcmp(pszEventMessage, "EVENT_DoorTransitionHallwayHall"))
			pDestEntity = pTestLevel->m_pDoorEntityHallHallway;
		else if (!strcmp(pszEventMessage, "EVENT_DoorTransitionHallHallway"))
			pDestEntity = pTestLevel->m_pDoorEntityHallwayHall;

		if (!pDestEntity)
			return true;

		if (!bNeedCancelEvent)
		{
			if (pActorEntity->GetOrigin() == pThisEntity->GetOrigin() || pTestLevel->m_bNextDoor)
			{ 
				pTestLevel->m_bProcessDoor = true;

				pActorEntity->SetVisible(false);

				pThisEntity->GetAnimCompositionController()->PlayAnimation(pTestLevel->m_WoodyDoorLeave, true);

				/*if (pTestLevel->m_LastAnimCount)
				{
					pThisEntity->GetAnimCompositionController()->SetCurrentAnimationCompositionCount(pTestLevel->m_LastAnimCount);
					pTestLevel->m_LastAnimCount = 0;
				}*/

				if (!pTestLevel->m_bNextDoor && pThisEntity->GetAnimCompositionController()->IsAnimationCycleComplete())
				{
					pActorEntity->SetOrigin(pDestEntity->GetOrigin());
					pDestEntity->GetAnimCompositionController()->PlayAnimation(pTestLevel->m_WoodyDoorEnter, true);
					pTestLevel->m_bNextDoor = true;
				}

				if (pTestLevel->m_bNextDoor && pDestEntity->GetAnimCompositionController()->IsAnimationCycleComplete())
				{
					ResetDoorState(pThisEntity, pDestEntity, pActorEntity);
					pTestLevel->m_bNextDoor = false;
					pTestLevel->m_bProcessDoor = false;
					return true;
				}
			}
		}
		else
		{
			auto TargetEntity = pTestLevel->m_bNextDoor ? pDestEntity : pThisEntity;

			TargetEntity->GetAnimCompositionController()->SetAnimationMode(true);

			if (pTestLevel->m_bWayback && pTestLevel->m_bNextDoor)
			{
				TargetEntity->GetAnimCompositionController()->SetAnimationMode(false);

				pApi->GetInteractionMessagesList()->AddInteractionMessageForEntityName(
					szDoorIntercationClassID,
					pTestLevel->GetDoorEventTypeFromEntity(pDestEntity),
					pDestEntity->GetEntityName(),
					&pActorEntity,
					pTestLevel);

				pTestLevel->m_LastAnimCount = pDestEntity->GetAnimCompositionController()->GetCurrentAnimationCompositionCount();
				pTestLevel->m_pCurrentDoorEntity = pDestEntity;
				pTestLevel->m_HouseRoomTarget = HOUSE_ROOM::ROOM_EMPTY;
			}
			else
			{
				if (!TargetEntity->GetAnimCompositionController()->IsAnimationCycleComplete())
					return false;

				pTestLevel->m_pCurrentDoorEntity = nullptr;
			}

			ResetDoorState(pThisEntity, pDestEntity, pActorEntity);
			pTestLevel->m_bNextDoor = false;
			pTestLevel->m_bProcessDoor = false;
			pTestLevel->m_bWayback = false;
			pTestLevel->m_MovePoint.Clear();
			return true;
		}
	}

	return false;
}

CTestLevel::CTestLevel()
{
	this->m_WorldZoom = 0.f;
	this->m_bProcessDoor = false;
	this->m_bNextDoor = false;
}

CTestLevel::~CTestLevel()
{

}

void CTestLevel::OnLoadScene(IANApi* pApi)
{
	pApi->CreateAnimationComposition(pszWorld, 1, &this->m_WorldComposition);
	pApi->CreateAnimationComposition(pszWoody, 3, &this->m_WoodyComposition);
	pApi->CreateAnimationComposition(pszWoodyLeft, 8, &this->m_WoodyCompositionLeft);
	pApi->CreateAnimationComposition(pszWoodyRight, 8, &this->m_WoodyCompositionRight);
	pApi->CreateAnimationComposition(pszWoodyDoor, 10, &this->m_WoodyDoorLeave);
	pApi->CreateAnimationComposition(pszWoodyDoorEnter, 16, &this->m_WoodyDoorEnter);
	pApi->CreateAnimationComposition(pszDoorAnim, 1, &this->m_DoorComposition);

	pApi->RegWorld(&this->m_pWorld);
	this->m_pWorld->SetWorldSize(pApi->GetImageSize(pApi->GetAnimationCompositionFrameFromID(this->m_WorldComposition, 0)));
	this->m_pWorld->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_WorldComposition);

	pApi->RegEntity(&this->m_pMainActor, "CLASSID_Player");
	this->m_pMainActor->SetEntityName("ENTITY_Woody");
	this->m_pMainActor->SetOrigin(this->m_pWorld->GetMetrics().m_WorldSize * 0.5f);

	CreateDoorEntity(pApi, this->m_pDoorEntityHallwayKitchen, "ENTITY_DoorEntityHallwayKitchen", anVec2(1111.f, 550.f));
	CreateDoorEntity(pApi, this->m_pDoorEntityKitchenHallway, "ENTITY_DoorEntityKitchenHallway", anVec2(1095.f, 270.f));
	CreateDoorEntity(pApi, this->m_pDoorEntityHallwayHall, "ENTITY_DoorEntityHallwayHall", anVec2(500.f, 550.f));
	CreateDoorEntity(pApi, this->m_pDoorEntityHallHallway, "ENTITY_DoorEntityHallHallway", anVec2(500.f, 270.f));
}

void CTestLevel::OnUnloadScene(IANApi* pApi)
{
	pApi->DeleteAnimationComposition(&this->m_WorldComposition);
	pApi->DeleteAnimationComposition(&this->m_DoorComposition);
	pApi->DeleteAnimationComposition(&this->m_WoodyDoorLeave);
	pApi->DeleteAnimationComposition(&this->m_WoodyDoorEnter);
	pApi->DeleteAnimationComposition(&this->m_WoodyComposition);
	pApi->DeleteAnimationComposition(&this->m_WoodyCompositionLeft);
	pApi->DeleteAnimationComposition(&this->m_WoodyCompositionRight);
	
	pApi->UnregWorld(&this->m_pWorld);

	pApi->UnregAndDeleteAllEntity();

	pApi->GetInteractionMessagesList()->Clear();
}

void CTestLevel::Entry(IANApi* pApi)
{
	this->m_pMainActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyComposition);
	this->m_pMainActor->GetAnimCompositionController()->SetAnimationDuration(0.3f);

	KeyboardMoveInput(pApi);
		
	if (anRect(
		pApi->WorldToScreen(this->m_pWorld, anVec2(370.f, 380.f)),
		pApi->WorldToScreen(this->m_pWorld, anVec2(1227.f, 628.f))).IsIntersected(pApi->GetCursorPos()))
	{
		this->m_WoodyLocationRoomTarget = HOUSE_ROOM::HALLWAY;
		if (pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
		{
			this->m_HouseRoomTarget = HOUSE_ROOM::HALLWAY;
			this->m_MovePoint = pApi->ScreenPointToWorld(this->m_pWorld, pApi->GetCursorPos());
		}
	}

	if (anRect(
		pApi->WorldToScreen(this->m_pWorld, anVec2(87.f, 380.f)),
		pApi->WorldToScreen(this->m_pWorld, anVec2(356.f, 628.f))).IsIntersected(pApi->GetCursorPos()))
	{
		this->m_WoodyLocationRoomTarget = HOUSE_ROOM::BATHROOM;
		if (pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
		{
			this->m_HouseRoomTarget = HOUSE_ROOM::BATHROOM;
			this->m_MovePoint = pApi->ScreenPointToWorld(this->m_pWorld, pApi->GetCursorPos());
		}
	}

	if (anRect(
		pApi->WorldToScreen(this->m_pWorld, anVec2(847.f, 87.f)),
		pApi->WorldToScreen(this->m_pWorld, anVec2(1356.f, 341.f))).IsIntersected(pApi->GetCursorPos()))
	{
		this->m_WoodyLocationRoomTarget = HOUSE_ROOM::KITCHEN;
		if (pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
		{
			this->m_HouseRoomTarget = HOUSE_ROOM::KITCHEN;
			this->m_MovePoint = pApi->ScreenPointToWorld(this->m_pWorld, pApi->GetCursorPos());
		}
	}

	if (anRect(
		pApi->WorldToScreen(this->m_pWorld, anVec2(123.f, 87.f)), 
		pApi->WorldToScreen(this->m_pWorld, anVec2(825.f, 341.f))).IsIntersected(pApi->GetCursorPos()))
	{
		this->m_WoodyLocationRoomTarget = HOUSE_ROOM::HALL;
		if (pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
		{
			this->m_HouseRoomTarget = HOUSE_ROOM::HALL;
			this->m_MovePoint = pApi->ScreenPointToWorld(this->m_pWorld, pApi->GetCursorPos());
		}
	}

	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallwayKitchen);
	ProcessDoorInteraction(pApi, this->m_pDoorEntityKitchenHallway);
	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallwayHall);
	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallHallway);

	ProcessActorMove(pApi);
	DrawWorld(pApi);
	DrawEntities(pApi);
	DrawStatistics(pApi);
	DrawUI(pApi);

	auto ScreenSize = pApi->GetScreenSize();
	pApi->DrawLine(anVec2(ScreenSize.x * 0.5f, 0.f), anVec2(ScreenSize.x * 0.5f, ScreenSize.y), anColor::White(), 5.f);
	pApi->DrawLine(anVec2(0.f, ScreenSize.y * 0.5f), anVec2(ScreenSize.x, ScreenSize.y * 0.5f), anColor::White(), 5.f);
}

const char* CTestLevel::GetDoorEventTypeFromEntity(IANEntity* pEntity)
{
	auto EntityName = pEntity->GetEntityName();

	if (!strcmp(EntityName, "ENTITY_DoorEntityHallwayKitchen"))
		return "EVENT_DoorTransitionHallwayKitchen";
	else if (!strcmp(EntityName, "ENTITY_DoorEntityKitchenHallway"))
		return "EVENT_DoorTransitionKitchenHallway";
	else if (!strcmp(EntityName, "ENTITY_DoorEntityHallwayHall"))
		return "EVENT_DoorTransitionHallwayHall";
	else if (!strcmp(EntityName, "ENTITY_DoorEntityHallHallway"))
		return "EVENT_DoorTransitionHallHallway";

	return nullptr;
}

void CTestLevel::KeyboardMoveInput(IANApi* pApi)
{
	if (pApi->GetKeyIsDowned('W'))
		this->m_pMainActor->MoveUp(pApi, Step);
	if (pApi->GetKeyIsDowned('S'))
		this->m_pMainActor->MoveDown(pApi, Step);
	if (pApi->GetKeyIsDowned('A'))
	{
		this->m_pMainActor->MoveLeft(pApi, Step);
		this->m_pMainActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyCompositionLeft);
		this->m_pMainActor->GetAnimCompositionController()->SetAnimationDuration(0.1f);
	}
	if (pApi->GetKeyIsDowned('D'))
	{
		this->m_pMainActor->MoveRight(pApi, Step);
		this->m_pMainActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyCompositionRight);
		this->m_pMainActor->GetAnimCompositionController()->SetAnimationDuration(0.1f);
	}
}

void CTestLevel::DrawWorld(IANApi* pApi)
{
	this->m_pWorld->SetZoom(this->m_WorldZoom);
	this->m_pWorld->SetCameraToEntity(this->m_pMainActor);
	this->m_pWorld->Update(pApi);
	this->m_pWorld->Draw(pApi);
}

void CTestLevel::DrawEntities(IANApi* pApi)
{
	pApi->FindEntityByGroupID("CLASSID_WorldEntity")->Update(pApi).Draw(pApi, this->m_pWorld);
	pApi->FindEntityByGroupID("CLASSID_Player")->SortByYOrder().Update(pApi).Draw(pApi, this->m_pWorld);
}

void CTestLevel::DrawUI(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	if (pApi->AddButton("Go to menu", anVec2(ScreenSize.x - 130.f - 5.f, ScreenSize.y - 50.f - 5.f), anVec2(130.f, 50.f)))
		pApi->ConnectToScene(new CTestGameScene());

	pApi->PushFontColor(anColor::White());
	pApi->AddSliderFloat("Map zoom", anVec2(10.f, ScreenSize.y - 70.f), anVec2(300.f, 30.f), 0.f, 10000.f, &this->m_WorldZoom);
	pApi->PopFontColor();
}

void CTestLevel::DrawStatistics(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	auto WorldMetrics = this->m_pWorld->GetMetrics();
	auto ActorScreen = pApi->WorldToScreen(this->m_pWorld, this->m_pMainActor);
	char buff[512] = { 0 };
	sprintf_s(buff, "FPS: %d\n"
		"Frametime: %f\n"
		"Screen size: %.1f:%.1f\n"
		"World Size: %.1f:%.1f\n"
		"World pos: %.1f:%.1f\n"
		"World screen size: %.1f:%.1f\n"
		"Camera world: %.1f:%.1f\n"
		"Camera screen: %.1f:%.1f\n"
		"Actor world: %f:%f\n"
		"Actor screen: %.1f:%.1f\n"
		"Cursor screen: %.1f:%.1f",
		pApi->FPS,
		pApi->Frametime,
		ScreenSize.x, ScreenSize.y,
		WorldMetrics.m_WorldSize.x, WorldMetrics.m_WorldSize.y,
		WorldMetrics.m_WorldScreenPos.x, WorldMetrics.m_WorldScreenPos.y,
		WorldMetrics.m_WorldScreenSize.x, WorldMetrics.m_WorldScreenSize.y,
		WorldMetrics.m_CameraWorld.x, WorldMetrics.m_CameraWorld.y,
		WorldMetrics.m_CameraScreen.x, WorldMetrics.m_CameraScreen.y,
		this->m_pMainActor->GetOrigin().x, this->m_pMainActor->GetOrigin().y,
		ActorScreen.x, ActorScreen.y,
		pApi->GetCursorPos().x, pApi->GetCursorPos().y);

	pApi->TextDraw(buff, anVec2(10.f, 20.f), anColor::White());
}

bool CTestLevel::ProcessDoorInteraction(IANApi* pApi, IANEntity*& pEntity)
{
	if (pEntity->IsScreenPointIntersected(pApi, this->m_pWorld, pApi->GetCursorPos()) && pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
	{
		if (this->m_pCurrentDoorEntity == pEntity)
		{
			pApi->GetInteractionMessagesList()->SendCancelInteractionMessageForClassID(szDoorIntercationClassID);
			this->m_bWayback = true;
		}
		else
			this->m_pCurrentDoorEntity = pEntity;

		if (pEntity == this->m_pDoorEntityHallwayKitchen)
		{
			this->m_CurrentDoorTarget = DOOR_INTERACTIONS::DOOR_HALLWAY_KITCHEN;
			this->m_MovePoint = pEntity->GetOrigin();
			return true;
		}
		else if (pEntity == this->m_pDoorEntityHallwayHall)
		{
			this->m_CurrentDoorTarget = DOOR_INTERACTIONS::DOOR_HALLWAY_HALL;
			this->m_MovePoint = pEntity->GetOrigin();
			return true;
		}
		else if (pEntity == this->m_pDoorEntityKitchenHallway)
		{
			this->m_CurrentDoorTarget = DOOR_INTERACTIONS::DOOR_KITCHEN_HALLWAY;
			this->m_MovePoint = pEntity->GetOrigin();
			return true;
		}	
		else if (pEntity == this->m_pDoorEntityHallHallway)
		{
			this->m_CurrentDoorTarget = DOOR_INTERACTIONS::DOOR_HALL_HALLWAY;
			this->m_MovePoint = pEntity->GetOrigin();
			return true;
		}
	}

	return false;
}

void CTestLevel::ProcessActorMove(IANApi* pApi)
{
	if (!!this->m_MovePoint)
	{
		auto ActorOrigin = this->m_pMainActor->GetOrigin();

		auto IsDoor = this->m_CurrentDoorTarget != DOOR_INTERACTIONS::DOOR_EMPTY;

		if (!IsDoor || (IsDoor && ActorOrigin.x != this->m_MovePoint.x))
		{
			switch (this->m_HouseRoomTarget)
			{
			case HOUSE_ROOM::HALLWAY:
			case HOUSE_ROOM::BATHROOM:
				this->m_MovePoint.y = 611.f;
				break;
			case HOUSE_ROOM::KITCHEN:
			case HOUSE_ROOM::HALL:
				this->m_MovePoint.y = 326.f;
				break;
			}
		}

		if (this->m_bProcessDoor)
			return;

		if (ActorOrigin.y != this->m_MovePoint.y)
		{
			this->m_pMainActor->MoveVertical(pApi, Step, this->m_MovePoint.y);
		}
		else
		{
			this->m_pMainActor->MoveHorizontal(pApi, Step, this->m_MovePoint.x);

			IANEntity* pTargetDoorEntity = nullptr;
			const char* szEventName = nullptr;

			if (IsDoor)
			{
				switch (this->m_CurrentDoorTarget)
				{
				case DOOR_INTERACTIONS::DOOR_HALLWAY_KITCHEN:
					szEventName = "EVENT_DoorTransitionHallwayKitchen";
					pTargetDoorEntity = this->m_pDoorEntityHallwayKitchen;
					break;
				case DOOR_INTERACTIONS::DOOR_HALLWAY_HALL:
					szEventName = "EVENT_DoorTransitionHallwayHall";
					pTargetDoorEntity = this->m_pDoorEntityHallwayHall;
					break;
				case DOOR_INTERACTIONS::DOOR_KITCHEN_HALLWAY:
					szEventName = "EVENT_DoorTransitionKitchenHallway";
					pTargetDoorEntity = this->m_pDoorEntityKitchenHallway;
					break;
				case DOOR_INTERACTIONS::DOOR_HALL_HALLWAY:
					szEventName = "EVENT_DoorTransitionHallHallway";
					pTargetDoorEntity = this->m_pDoorEntityHallHallway;
					break;
				}

				if (ActorOrigin.x == this->m_MovePoint.x)
					this->m_MovePoint.y = pTargetDoorEntity->GetOrigin().y;
			}

			if (ActorOrigin == this->m_MovePoint)
			{
				if (IsDoor)
				{
					auto iml = pApi->GetInteractionMessagesList();
					iml->SendCancelInteractionMessageForClassID(szDoorIntercationClassID);
					iml->AddInteractionMessageForEntityName(szDoorIntercationClassID,
						szEventName,
						pTargetDoorEntity->GetEntityName(),
						&this->m_pMainActor,
						this);
				}

				this->m_MovePoint.Clear();
				this->m_CurrentDoorTarget = DOOR_INTERACTIONS::DOOR_EMPTY;
			}
		}
	}
}

void CTestLevel::CreateDoorEntity(IANApi* pApi, IANEntity*& ppEntity, const char* pszDoorName, anVec2 Origin)
{
	pApi->RegEntity(&ppEntity, "CLASSID_WorldEntity");
	ppEntity->SetEntityName(pszDoorName);
	ppEntity->SetOrigin(Origin);
	ppEntity->SetInteractionController(new DoorEntityInteractionController);
	ppEntity->GetAnimCompositionController()->SetAnimationComposition(this->m_DoorComposition);
	ppEntity->GetAnimCompositionController()->SetAnimationDuration(0.1f);
}
