#include "../../includes.h"

float Step = 250.f;

auto szWorldEntityClassID_RoomZone = "CLASSID_WorldEntity_RoomZone";
auto szWorldEntityClassID_Door = "CLASSID_WorldEntity_Door";
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
				pTestLevel->m_CurrentActorInteractionDoorLeave = CTestLevel::GetUserData<CDoorEntityData>(pThisEntity)->m_DoorInteraction;
				pTestLevel->m_CurrentActorInteractionDoorEnter = CTestLevel::GetUserData<CDoorEntityData>(pDestEntity)->m_DoorInteraction;

				pTestLevel->m_LastLeaveActorIntercationDoor = pTestLevel->m_CurrentActorInteractionDoorLeave;
				pTestLevel->m_LastEnterActorIntercationDoor = pTestLevel->m_CurrentActorInteractionDoorEnter;

				pTestLevel->m_bProcessDoor = true;

				pActorEntity->SetVisible(false);

				pThisEntity->GetAnimCompositionController()->PlayAnimation(pTestLevel->m_WoodyDoorLeave, true);

				if (!pTestLevel->m_bNextDoor)
				{
					if (pThisEntity->GetAnimCompositionController()->IsAnimationCycleComplete())
					{
						pActorEntity->SetOrigin(pDestEntity->GetOrigin());
						pDestEntity->GetAnimCompositionController()->PlayAnimation(pTestLevel->m_WoodyDoorEnter, true);
						pTestLevel->m_bNextDoor = true;
					}
				}

				if (pTestLevel->m_bNextDoor && pDestEntity->GetAnimCompositionController()->IsAnimationCycleComplete())
				{
					ResetDoorState(pThisEntity, pDestEntity, pActorEntity);
					pTestLevel->m_bNextDoor = false;
					pTestLevel->m_bProcessDoor = false;
					pTestLevel->m_LeaveDoorEntity = pTestLevel->m_EnterDoorEntity = DOOR_INTERACTIONS::DOOR_EMPTY;
					pTestLevel->m_CurrentActorInteractionDoorLeave = pTestLevel->m_CurrentActorInteractionDoorEnter = DOOR_INTERACTIONS::DOOR_EMPTY;
					return true;
				}
			}
		}
		else
		{
			auto TargetEntity = pTestLevel->m_bNextDoor ? pDestEntity : pThisEntity;

			if (pTestLevel->m_bWayback && pTestLevel->m_bNextDoor)
			{
				pApi->GetInteractionMessagesList()->AddInteractionMessageForEntityName(
					szDoorIntercationClassID,
					pTestLevel->GetDoorEventTypeFromEntity(pDestEntity),
					pDestEntity->GetEntityName(),
					&pActorEntity,
					pTestLevel);

				pTestLevel->m_LastAnimCount = pDestEntity->GetAnimCompositionController()->GetCurrentAnimationCompositionCount();
				pTestLevel->m_HouseRoomTarget = HOUSE_ROOM::ROOM_EMPTY;
				pTestLevel->m_bProcessDoor = true;
			}
			else
			{
				TargetEntity->GetAnimCompositionController()->SetAnimationMode(true);

				if (!TargetEntity->GetAnimCompositionController()->IsAnimationCycleComplete())
					return false;

				if (pTestLevel->m_LastLeaveActorIntercationDoor == pTestLevel->m_LeaveDoorEntity || 
					pTestLevel->m_LastEnterActorIntercationDoor == pTestLevel->m_EnterDoorEntity)
				{
					pTestLevel->m_LeaveDoorEntity = pTestLevel->m_EnterDoorEntity = DOOR_INTERACTIONS::DOOR_EMPTY;
					pTestLevel->m_LastLeaveActorIntercationDoor = pTestLevel->m_LastEnterActorIntercationDoor = DOOR_INTERACTIONS::DOOR_EMPTY;
				}

				pTestLevel->m_bProcessDoor = false;
			}

			ResetDoorState(pThisEntity, pDestEntity, pActorEntity);
			pTestLevel->m_bNextDoor = false;
			pTestLevel->m_bWayback = false;
			pTestLevel->m_CurrentActorInteractionDoorLeave = pTestLevel->m_CurrentActorInteractionDoorEnter = DOOR_INTERACTIONS::DOOR_EMPTY;
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
	this->m_pWorld->GetAnimCompositionController()->SetAnimationComposition(this->m_WorldComposition);

	pApi->RegEntity(&this->m_pMainActor, "CLASSID_Player");
	this->m_pMainActor->SetEntityName("ENTITY_Woody");
	this->m_pMainActor->SetOrigin(this->m_pWorld->GetMetrics().m_WorldSize * 0.5f);

	CreateDoorEntity(pApi, this->m_pDoorEntityHallwayKitchen, "ENTITY_DoorEntityHallwayKitchen", anVec2(1111.f, 550.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_KITCHEN, DOOR_INTERACTIONS::DOOR_KITCHEN_HALLWAY, 1);
	CreateDoorEntity(pApi, this->m_pDoorEntityKitchenHallway, "ENTITY_DoorEntityKitchenHallway", anVec2(1095.f, 270.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::KITCHEN, DOOR_INTERACTIONS::DOOR_KITCHEN_HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_KITCHEN, 2);
	CreateDoorEntity(pApi, this->m_pDoorEntityHallwayHall, "ENTITY_DoorEntityHallwayHall", anVec2(500.f, 550.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_HALL, DOOR_INTERACTIONS::DOOR_HALL_HALLWAY, 1);
	CreateDoorEntity(pApi, this->m_pDoorEntityHallHallway, "ENTITY_DoorEntityHallHallway", anVec2(500.f, 270.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::HALL, DOOR_INTERACTIONS::DOOR_HALL_HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_HALL, 2);

	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneHallway, anVec2(370.f, 380.f), anVec2(857.f, 248.f), HOUSE_ROOM::HALLWAY, 1);
	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneBathroom, anVec2(84.f, 377.f), anVec2(269.f, 254.f), HOUSE_ROOM::BATHROOM, 1);
	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneKitchen, anVec2(847.f, 98.f), anVec2(509.f, 250.f), HOUSE_ROOM::KITCHEN, 2);
	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneHall, anVec2(123.f, 98.f), anVec2(702.f, 247.f), HOUSE_ROOM::HALL, 2);
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

	ProcessActorMove(pApi);
	DrawWorld(pApi);
	DrawEntities(pApi);
	DrawUI(pApi);
#if DEBUG_LEVEL_1 == 1
	DrawStatistics(pApi);
#endif
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
#if DEBUG_LEVEL_1 == 1
	auto Zone = pApi->FindEntityByGroupID(szWorldEntityClassID_RoomZone);

	for (auto& re : Zone->m_EntityGroup)
	{
		auto ScreenF = pApi->WorldToScreen(this->m_pWorld, re->GetOrigin());
		auto ScreenS = pApi->WorldToScreen(this->m_pWorld, re->GetOrigin() + re->GetEntitySize());
		pApi->DrawRectangle(ScreenF, ScreenS - ScreenF, anRect(re->GetOrigin(), re->GetOrigin() + re->GetEntitySize()).IsIntersected(this->m_pMainActor->GetOrigin()) ? anColor::Blue() : anColor::Red(), 3.f);
	}
#endif
	pApi->FindEntityByGroupID(szWorldEntityClassID_Door)->Update(pApi).Draw(pApi, this->m_pWorld);
	pApi->FindEntityByGroupID("CLASSID_WorldEntity")->Update(pApi).Draw(pApi, this->m_pWorld);
	pApi->FindEntityByGroupID("CLASSID_Player")->SortByYOrder().Update(pApi).Draw(pApi, this->m_pWorld);
}

void CTestLevel::DrawUI(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	if (pApi->AddButton("Go to menu", anVec2(ScreenSize.x - 130.f - 5.f, ScreenSize.y - 50.f - 5.f), anVec2(130.f, 50.f)))
		pApi->ConnectToScene(new CTestGameScene());
}

void CTestLevel::DrawStatistics(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	pApi->DrawLine(anVec2(ScreenSize.x * 0.5f, 0.f), anVec2(ScreenSize.x * 0.5f, ScreenSize.y), anColor::White(), 5.f);
	pApi->DrawLine(anVec2(0.f, ScreenSize.y * 0.5f), anVec2(ScreenSize.x, ScreenSize.y * 0.5f), anColor::White(), 5.f);

	auto WorldMetrics = this->m_pWorld->GetMetrics();
	auto ActorScreen = pApi->WorldToScreen(this->m_pWorld, this->m_pMainActor);
	char buff[1024] = { 0 };
	sprintf_s(buff,
		"ENGINE:\n"
		"FPS: %d\n"
		"Frametime: %f\n"
		"Screen size: %.1f:%.1f\n"
		"World Size: %.1f:%.1f\n"
		"World pos: %.1f:%.1f\n"
		"World screen size: %.1f:%.1f\n"
		"Camera world: %.1f:%.1f\n"
		"Camera screen: %.1f:%.1f\n"
		"Actor world: %f:%f\n"
		"Actor screen: %.1f:%.1f\n"
		"Cursor screen: %.1f:%.1f\n\n"
		"GAME DATA:\n"
		"m_bProcessDoor: %d\n"
		"m_bNextDoor: %d\n"
		"m_bWayback: %d\n"
		"m_LeaveDoorEntity: %d\n"
		"m_EnterDoorEntity: %d\n"
		"m_iCurrentActorFloor: %d\n"
		"m_iTargetFloor: %d",
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
		pApi->GetCursorPos().x, pApi->GetCursorPos().y,
		this->m_bProcessDoor,
		this->m_bNextDoor,
		this->m_bWayback,
		this->m_LeaveDoorEntity,
		this->m_EnterDoorEntity,
		this->m_iCurrentActorFloor,
		this->m_iTargetFloor);

	pApi->PushFontAppierence(FontAppierence::FONT_SHADOW);
	pApi->TextDraw(buff, anVec2(10.f, 20.f), anColor::White());
	pApi->PopFontAppierence();

	pApi->PushFontColor(anColor::White());
	pApi->AddSliderFloat("Map zoom", anVec2(10.f, ScreenSize.y - 70.f), anVec2(300.f, 30.f), 0.f, 10000.f, &this->m_WorldZoom);
	pApi->PopFontColor();
}

bool CTestLevel::ProcessDoorInteraction(IANApi* pApi, IANEntity*& pEntity)
{
	if (pEntity->IsScreenPointIntersected(pApi, this->m_pWorld, pApi->GetCursorPos()) && pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
	{
		auto DoorEntData = CTestLevel::GetUserData<CDoorEntityData>(pEntity);

		if (this->m_bProcessDoor && (this->m_LastLeaveActorIntercationDoor == DoorEntData->m_DoorInteraction || (this->m_LastEnterActorIntercationDoor == DoorEntData->m_DoorInteraction)))
		{
			pApi->GetInteractionMessagesList()->SendCancelInteractionMessageForClassID(szDoorIntercationClassID);
			this->m_MovePoint = NULL;
			this->m_bWayback = true;
			this->m_LeaveDoorEntity = DoorEntData->m_DoorInteraction;
			return true;
		}

		if (this->m_CurrentActorInteractionDoorLeave != DOOR_INTERACTIONS::DOOR_EMPTY && this->m_LeaveDoorEntity != DoorEntData->m_DoorInteraction)
		{
			pApi->GetInteractionMessagesList()->SendCancelInteractionMessageForClassID(szDoorIntercationClassID);

			if (DoorEntData->m_LevelFloor != this->m_iCurrentActorFloor)
				this->m_bWayback = true;
		}

		this->m_CurrentDoorTarget = DoorEntData->m_DoorInteraction;
		this->m_MovePoint = pEntity->GetOrigin();
		this->m_LeaveDoorEntity = DoorEntData->m_DoorInteraction;
		this->m_EnterDoorEntity = DoorEntData->m_InvertedDoorInteraction;
		this->m_iTargetFloor = DoorEntData->m_LevelFloor;
		return true;
	}

	return false;
}

void CTestLevel::ProcessActorMove(IANApi* pApi)
{
	bool bOnRoom = false;

	auto RoomZoneSections = pApi->FindEntityByGroupID(szWorldEntityClassID_RoomZone);

	for (auto& re : RoomZoneSections->m_EntityGroup)
	{
		if (anRect(re->GetOrigin(), re->GetOrigin() + re->GetEntitySize()).IsIntersected(this->m_pMainActor->GetOrigin()))
		{
			this->m_iCurrentActorFloor = CTestLevel::GetUserData<CRoomZoneEntityData>(re)->m_LevelFloor;
			bOnRoom = true;
		}
	}

	if (!bOnRoom)
		this->m_iCurrentActorFloor = -INT_MAX;

	bool bOnDoor = false;

	auto DoorGroup = pApi->FindEntityByGroupID(szWorldEntityClassID_Door);
	for (auto& de : DoorGroup->m_EntityGroup)
	{
		if (pApi->CalcBBox(this->m_pWorld, de->GetOrigin(), de->CalcEntitySize(pApi)).IsIntersected(pApi->GetCursorPos()))
		{
			bOnDoor = true;
			break;
		}
	}

	if (!bOnDoor && pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
	{
		for (auto& re : RoomZoneSections->m_EntityGroup)
		{
			if (anRect(
				pApi->WorldToScreen(this->m_pWorld, re->GetOrigin()),
				pApi->WorldToScreen(this->m_pWorld, re->GetOrigin() + re->GetEntitySize())).IsIntersected(pApi->GetCursorPos()))
			{
				this->m_iTargetFloor = CTestLevel::GetUserData<CRoomZoneEntityData>(re)->m_LevelFloor;

				pApi->GetInteractionMessagesList()->SendCancelInteractionMessageForClassID(szDoorIntercationClassID);

				if (!this->m_bProcessDoor)
					this->m_LeaveDoorEntity = this->m_EnterDoorEntity = DOOR_INTERACTIONS::DOOR_EMPTY;

				this->m_CurrentDoorTarget = DOOR_INTERACTIONS::DOOR_EMPTY;
				this->m_HouseRoomTarget = CTestLevel::GetUserData<CRoomZoneEntityData>(re)->m_HouseRoom;
				this->m_MovePoint = pApi->ScreenPointToWorld(this->m_pWorld, pApi->GetCursorPos());
			}
		}
	}

	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallwayKitchen);
	ProcessDoorInteraction(pApi, this->m_pDoorEntityKitchenHallway);
	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallwayHall);
	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallHallway);

	if (this->m_MovePoint.IsValid() && !this->m_bProcessDoor)
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
					pApi->GetInteractionMessagesList()->AddInteractionMessageForEntityName(
						szDoorIntercationClassID,
						szEventName,
						pTargetDoorEntity->GetEntityName(),
						&this->m_pMainActor,
						this);
				}

				this->m_MovePoint = NULL;
				this->m_CurrentDoorTarget = DOOR_INTERACTIONS::DOOR_EMPTY;
			}
		}
	}
}

void CTestLevel::CreateRoomZoneEntity(IANApi* pApi, IANEntity*& pEntity, anVec2 RoomPos, anVec2 RoomSize, HOUSE_ROOM HouseRoom, int iLevelFloor)
{
	pApi->RegEntity(&pEntity, szWorldEntityClassID_RoomZone);
	pEntity->SetOrigin(RoomPos);
	pEntity->SetEntitySize(RoomSize);
	pEntity->SetUserDataPointer(new CRoomZoneEntityData(HouseRoom, iLevelFloor));
}

void CTestLevel::CreateDoorEntity(IANApi* pApi, IANEntity*& pEntity, const char* pszDoorName, anVec2 Origin, DOOR_TYPE DoorType, HOUSE_ROOM HouseRoom, DOOR_INTERACTIONS DoorInteraction, DOOR_INTERACTIONS InvertedDoorInteraction, int iLevelFloor)
{
	pApi->RegEntity(&pEntity, szWorldEntityClassID_Door);
	pEntity->SetEntityName(pszDoorName);
	pEntity->SetOrigin(Origin);
	pEntity->SetInteractionController(new DoorEntityInteractionController);
	pEntity->GetAnimCompositionController()->SetAnimationComposition(this->m_DoorComposition);
	pEntity->GetAnimCompositionController()->SetAnimationDuration(0.1f);
	pEntity->SetUserDataPointer(new CDoorEntityData(HouseRoom, DoorType, DoorInteraction, InvertedDoorInteraction, iLevelFloor));
}
