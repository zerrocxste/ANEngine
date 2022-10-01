#include "../../includes.h"

float Step = 250.f;

auto szWorldEntityPlayer = "CLASSID_WorldEntity_Player";
auto szWorldEntityClassIDRoomZone = "CLASSID_WorldEntity_RoomZone";
auto szWorldEntityClassIDDoor = "CLASSID_WorldEntity_Door";

auto szDoorIntercationClassID = "CLASSID_EVENT_Door";

const char* pszWorld[] = { 
	"house15.bmp" 
};
const char* pszWoody[] = { 
	"w_ms2_0004.png", 
	"w_ms2_0005.png", 
	"w_ms2_0006.png" 
};
const char* pszWoodyUp[] = {
	"walk_up\\W_mg0_0000.png",
	"walk_up\\W_mg0_0001.png",
	"walk_up\\W_mg0_0002.png",
	"walk_up\\W_mg0_0003.png",
	"walk_up\\W_mg0_0004.png",
	"walk_up\\W_mg0_0005.png",
	"walk_up\\W_mg0_0006.png",
	"walk_up\\W_mg0_0007.png"
};
const char* pszWoodyDown[] = {
	"walk_down\\W_mg2_0000.png",
	"walk_down\\W_mg2_0001.png",
	"walk_down\\W_mg2_0002.png",
	"walk_down\\W_mg2_0003.png",
	"walk_down\\W_mg2_0004.png",
	"walk_down\\W_mg2_0005.png",
	"walk_down\\W_mg2_0006.png",
	"walk_down\\W_mg2_0007.png"
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
	"door_vertical\\W_leave_0000.png", 
	"door_vertical\\W_leave_0001.png", 
	"door_vertical\\W_leave_0002.png", 
	"door_vertical\\W_leave_0003.png",
	"door_vertical\\W_leave_0004.png", 
	"door_vertical\\W_leave_0005.png", 
	"door_vertical\\W_leave_0006.png", 
	"door_vertical\\W_leave_0007.png", 
	"door_vertical\\W_leave_0008.png", 
	"door_vertical\\W_leave_0009.png",
};
const char* pszWoodyDoorEnter[] = {
	"door_vertical\\W_enter_0015.png",
	"door_vertical\\W_enter_0014.png",
	"door_vertical\\W_enter_0013.png",
	"door_vertical\\W_enter_0012.png",
	"door_vertical\\W_enter_0011.png",
	"door_vertical\\W_enter_0010.png",
	"door_vertical\\W_enter_0009.png",
	"door_vertical\\W_enter_0008.png",
	"door_vertical\\W_enter_0007.png",
	"door_vertical\\W_enter_0006.png",
	"door_vertical\\W_enter_0005.png",
	"door_vertical\\W_enter_0004.png",
	"door_vertical\\W_enter_0003.png",
	"door_vertical\\W_enter_0002.png",
	"door_vertical\\W_enter_0001.png",
	"door_vertical\\W_enter_0000.png",
};
const char* pszWoodySideDoorLeftEnter[] = {
	"side_door_left\\W_enter_0000.png",
	"side_door_left\\W_enter_0001.png",
	"side_door_left\\W_enter_0002.png",
	"side_door_left\\W_enter_0003.png",
	"side_door_left\\W_enter_0004.png",
	"side_door_left\\W_enter_0005.png",
	"side_door_left\\W_enter_0006.png",
	"side_door_left\\W_enter_0007.png",
	"side_door_left\\W_enter_0008.png",
	"side_door_left\\W_enter_0009.png",
	"side_door_left\\W_enter_0010.png",
	"side_door_left\\W_enter_0011.png",
	"side_door_left\\W_enter_0012.png",
	"side_door_left\\W_enter_0013.png",
	"side_door_left\\W_enter_0014.png",
	"side_door_left\\W_enter_0015.png",
	"side_door_left\\W_enter_0016.png",
	"side_door_left\\W_enter_0017.png",
	"side_door_left\\W_enter_0018.png",
	"side_door_left\\W_enter_0019.png",
	"side_door_left\\W_enter_0020.png",
	"side_door_left\\W_enter_0021.png",
	"side_door_left\\W_enter_0022.png",
	"side_door_left\\W_enter_0023.png",
	"side_door_left\\W_enter_0024.png",
};
const char* pszWoodySideDoorRightEnter[] = {
	"side_door_right\\W_enter_0000.png",
	"side_door_right\\W_enter_0001.png",
	"side_door_right\\W_enter_0002.png",
	"side_door_right\\W_enter_0003.png",
	"side_door_right\\W_enter_0004.png",
	"side_door_right\\W_enter_0005.png",
	"side_door_right\\W_enter_0006.png",
	"side_door_right\\W_enter_0007.png",
	"side_door_right\\W_enter_0008.png",
	"side_door_right\\W_enter_0009.png",
	"side_door_right\\W_enter_0010.png",
	"side_door_right\\W_enter_0011.png",
	"side_door_right\\W_enter_0012.png",
	"side_door_right\\W_enter_0013.png",
	"side_door_right\\W_enter_0014.png",
	"side_door_right\\W_enter_0015.png",
	"side_door_right\\W_enter_0016.png",
	"side_door_right\\W_enter_0017.png",
	"side_door_right\\W_enter_0018.png",
	"side_door_right\\W_enter_0019.png",
	"side_door_right\\W_enter_0020.png",
	"side_door_right\\W_enter_0021.png",
};
const char* pszDoorAnim[] = { 
	"N_leave_0000.png"
};
const char* pszDoorAnimLeft[] = {
	"side_door_left\\W_enter_0024.png"
};
const char* pszDoorAnimRight[] = {
	"side_door_right\\W_enter_0000.png"
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

	

	return false;
}

CTestLevel::CTestLevel()
{
	this->m_WorldZoom = 0.f;
}

CTestLevel::~CTestLevel()
{

}

void CTestLevel::OnLoadScene(IANApi* pApi)
{
	pApi->CreateAnimationComposition(pszWorld, 1, &this->m_WorldComposition);
	pApi->CreateAnimationComposition(pszWoody, 3, &this->m_WoodyComposition);
	pApi->CreateAnimationComposition(pszWoodyUp, 8, &this->m_WoodyCompositionUp);
	pApi->CreateAnimationComposition(pszWoodyDown, 8, &this->m_WoodyCompositionDown);
	pApi->CreateAnimationComposition(pszWoodyLeft, 8, &this->m_WoodyCompositionLeft);
	pApi->CreateAnimationComposition(pszWoodyRight, 8, &this->m_WoodyCompositionRight);
	pApi->CreateAnimationComposition(pszWoodyDoor, 10, &this->m_WoodyDoorLeave);
	pApi->CreateAnimationComposition(pszWoodyDoorEnter, 16, &this->m_WoodyDoorEnter);
	pApi->CreateAnimationComposition(pszWoodySideDoorLeftEnter, 25, &this->m_WoodyDoorSideLeftEnter);
	pApi->CreateAnimationComposition(pszWoodySideDoorRightEnter, 22, &this->m_WoodyDoorSideRightEnter);
	pApi->CreateAnimationComposition(pszDoorAnim, 1, &this->m_DoorComposition);
	pApi->CreateAnimationComposition(pszDoorAnimLeft, 1, &this->m_DoorCompositionLeft);
	pApi->CreateAnimationComposition(pszDoorAnimRight, 1, &this->m_DoorCompositionRight);

	pApi->RegWorld(&this->m_pWorld);
	this->m_pWorld->SetWorldSize(pApi->GetImageSize(pApi->GetAnimationCompositionFrameFromID(this->m_WorldComposition, 0)));
	this->m_pWorld->GetAnimCompositionController()->SetAnimationComposition(this->m_WorldComposition);

	CreateActorEntity(pApi, "ENTITY_Woody");

	CreateDoorEntity(pApi, this->m_pDoorEntityHallwayKitchen, "ENTITY_DoorEntityHallwayKitchen", anVec2(1111.f, 550.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_KITCHEN, DOOR_INTERACTIONS::DOOR_KITCHEN_HALLWAY, HOUSE_FLOOR::FIRST, this->m_DoorComposition);
	CreateDoorEntity(pApi, this->m_pDoorEntityKitchenHallway, "ENTITY_DoorEntityKitchenHallway", anVec2(1095.f, 270.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::KITCHEN, DOOR_INTERACTIONS::DOOR_KITCHEN_HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_KITCHEN, HOUSE_FLOOR::SECOND, this->m_DoorComposition);
	CreateDoorEntity(pApi, this->m_pDoorEntityHallwayHall, "ENTITY_DoorEntityHallwayHall", anVec2(500.f, 550.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_HALL, DOOR_INTERACTIONS::DOOR_HALL_HALLWAY, HOUSE_FLOOR::FIRST, this->m_DoorComposition);
	CreateDoorEntity(pApi, this->m_pDoorEntityHallHallway, "ENTITY_DoorEntityHallHallway", anVec2(500.f, 270.f), 
		DOOR_TYPE::VERTICAL, HOUSE_ROOM::HALL, DOOR_INTERACTIONS::DOOR_HALL_HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_HALL, HOUSE_FLOOR::SECOND, this->m_DoorComposition);

	CreateDoorEntity(pApi, this->m_pDoorEntityHallKitchen, "ENTITY_DoorEntityHallKitchen", anVec2(814.f, 345.f),
		DOOR_TYPE::HORIZONTAL, HOUSE_ROOM::HALL, DOOR_INTERACTIONS::DOOR_HALL_KITCHEN, DOOR_INTERACTIONS::DOOR_KITCHEN_HALL, HOUSE_FLOOR::SECOND, this->m_DoorCompositionRight);
	CreateDoorEntity(pApi, this->m_pDoorEntityKitchenHall, "ENTITY_DoorEntityKitchenHall", anVec2(862.f, 345.f),
		DOOR_TYPE::HORIZONTAL, HOUSE_ROOM::KITCHEN, DOOR_INTERACTIONS::DOOR_KITCHEN_HALL, DOOR_INTERACTIONS::DOOR_HALL_KITCHEN, HOUSE_FLOOR::SECOND, this->m_DoorCompositionLeft);

	CreateDoorEntity(pApi, this->m_pDoorEntityBathroomHallway, "ENTITY_DoorEntityBathroomHallway", anVec2(342.f, 622.f),
		DOOR_TYPE::HORIZONTAL, HOUSE_ROOM::BATHROOM, DOOR_INTERACTIONS::DOOR_BATHROOM_HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_BATHROOM, HOUSE_FLOOR::FIRST, this->m_DoorCompositionRight);
	CreateDoorEntity(pApi, this->m_pDoorEntityHallwayBathroom, "ENTITY_DoorEntityHallwayBathroom", anVec2(383.f, 622.f),
		DOOR_TYPE::HORIZONTAL, HOUSE_ROOM::HALLWAY, DOOR_INTERACTIONS::DOOR_HALLWAY_BATHROOM, DOOR_INTERACTIONS::DOOR_BATHROOM_HALLWAY, HOUSE_FLOOR::FIRST, this->m_DoorCompositionLeft);

	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneHallway, anVec2(798.5f, 628.f), anVec2(857.f, 248.f), HOUSE_ROOM::HALLWAY, HOUSE_FLOOR::FIRST);
	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneBathroom, anVec2(218.5f, 631.f), anVec2(269.f, 254.f), HOUSE_ROOM::BATHROOM, HOUSE_FLOOR::FIRST);
	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneKitchen, anVec2(1101.5f, 345.f), anVec2(509.f, 250.f), HOUSE_ROOM::KITCHEN, HOUSE_FLOOR::SECOND);
	CreateRoomZoneEntity(pApi, this->m_pEntityDoorZoneHall, anVec2(475.f, 345.f), anVec2(702.f, 247.f), HOUSE_ROOM::HALL, HOUSE_FLOOR::SECOND);
}

void CTestLevel::OnUnloadScene(IANApi* pApi)
{
	pApi->DeleteAnimationComposition(&this->m_WorldComposition);
	pApi->DeleteAnimationComposition(&this->m_DoorComposition);
	pApi->DeleteAnimationComposition(&this->m_WoodyDoorLeave);
	pApi->DeleteAnimationComposition(&this->m_WoodyDoorEnter);
	pApi->DeleteAnimationComposition(&this->m_WoodyComposition);
	pApi->DeleteAnimationComposition(&this->m_WoodyCompositionLeft);
	pApi->DeleteAnimationComposition(&this->m_WoodyDoorSideLeftEnter);
	pApi->DeleteAnimationComposition(&this->m_WoodyCompositionRight);
	
	pApi->UnregWorld(&this->m_pWorld);

	pApi->UnregAndDeleteAllEntity();

	pApi->GetInteractionMessagesList()->Clear();
}

void CTestLevel::Entry(IANApi* pApi)
{
	PreFrame(pApi);
	KeyboardMoveInput(pApi);
	CreateMove(pApi);
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
	else if (!strcmp(EntityName, "ENTITY_DoorEntityHallKitchen"))
		return "EVENT_DoorTransitionHallKitchen";
	else if (!strcmp(EntityName, "ENTITY_DoorEntityKitchenHall"))
		return "EVENT_DoorTransitionKitchenHall";

	return nullptr;
}

void CTestLevel::PreFrame(IANApi* pApi)
{
	this->m_pMainActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyComposition);
	this->m_pMainActor->GetAnimCompositionController()->SetAnimationDuration(0.3f);
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
		SetAnimationMoveLeft(this->m_pMainActor);
	}
	if (pApi->GetKeyIsDowned('D'))
	{
		this->m_pMainActor->MoveRight(pApi, Step);
		SetAnimationMoveRight(this->m_pMainActor);
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
	auto groupZone = pApi->FindEntityByGroupID(szWorldEntityClassIDRoomZone);

	for (auto ent = groupZone->First(); *ent != groupZone->Last(); (*ent)++)
	{
		auto entity = ent->Get();

		auto screenBBox = entity->CalcScreenBBox(pApi, this->m_pWorld);

		screenBBox = screenBBox.RecalcWithRelativeDistance();

		pApi->DrawRectangle(
			screenBBox.first,
			screenBBox.second,
			entity->IsScreenPointIntersected(pApi, this->m_pWorld, pApi->GetCursorPos()) ? anColor::Green() : anColor::Magenta(),
			5.f);
	}
#endif

	auto groupDoors = pApi->FindEntityByGroupID(szWorldEntityClassIDDoor);
	groupDoors->Update(pApi);
#if DEBUG_LEVEL_1 == 1
	groupDoors->DrawRectRegion(pApi, this->m_pWorld, anColor::Red());
#endif
	groupDoors->DrawFromComposition(pApi, this->m_pWorld);

	auto groupEntities = pApi->FindEntityByGroupID(szWorldEntityPlayer);
	groupEntities->SortByYOrder();
	groupEntities->Update(pApi);
#if DEBUG_LEVEL_1 == 1
	groupEntities->DrawRectRegion(pApi, this->m_pWorld, anColor::Blue());
#endif
	groupEntities->DrawFromComposition(pApi, this->m_pWorld);
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
		"Screen size: %.1f %.1f\n"
		"World Size: %.1f %.1f\n"
		"World pos: %.1f %.1f\n"
		"World screen size: %.1f %.1f\n"
		"Camera world: %.1f %.1f\n"
		"Camera screen: %.1f %.1f\n"
		"Actor world: %.1f %.1f\n"
		"Actor screen: %.1f %.1f\n"
		"Cursor screen: %.1f %.1f\n\n",
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

	pApi->PushFontAppierence(FontAppierence::FONT_SHADOW);
	pApi->TextDraw(buff, anVec2(10.f, 20.f), anColor::White());
	pApi->PopFontAppierence();

	pApi->PushFontColor(anColor::White());
	pApi->AddSliderFloat("Map zoom", anVec2(10.f, ScreenSize.y - 70.f), anVec2(300.f, 30.f), -1000.f, 10000.f, &this->m_WorldZoom);
	pApi->PopFontColor();
}

void CTestLevel::SetAnimationMoveUp(IANEntity* pActor)
{
	pActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyCompositionUp);
	pActor->GetAnimCompositionController()->SetAnimationDuration(0.08f);
}

void CTestLevel::SetAnimationMoveDown(IANEntity* pActor)
{
	pActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyCompositionDown);
	pActor->GetAnimCompositionController()->SetAnimationDuration(0.08f);
}

void CTestLevel::SetAnimationMoveLeft(IANEntity* pActor)
{
	pActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyCompositionLeft);
	pActor->GetAnimCompositionController()->SetAnimationDuration(0.08f);
}

void CTestLevel::SetAnimationMoveRight(IANEntity* pActor)
{
	pActor->GetAnimCompositionController()->SetAnimationComposition(this->m_WoodyCompositionRight);
	pActor->GetAnimCompositionController()->SetAnimationDuration(0.08f);
}

float CTestLevel::GetFloor(HOUSE_FLOOR Floor)
{
	float ret = FLT_MAX;

	if (Floor == HOUSE_FLOOR::FLOOR_UNK)
		Floor = GetWoodyEntityData(this->m_pMainActor).m_CurrentFloor;

	switch (Floor)
	{
	case HOUSE_FLOOR::FIRST:
		ret = 615.f;
		break;
	case HOUSE_FLOOR::SECOND:
		ret = 326.f;
		break;
	}

	return ret;
}

float CTestLevel::GetFloorFromRoom(HOUSE_ROOM Room)
{
	auto ret = 0.f;

	switch (Room)
	{
	case HALLWAY:
		ret = GetFloor(HOUSE_FLOOR::FIRST);
		break;
	case BATHROOM:
		ret = GetFloor(HOUSE_FLOOR::FIRST);
		break;
	case KITCHEN:
		ret = GetFloor(HOUSE_FLOOR::SECOND);
		break;
	case HALL:
		ret = GetFloor(HOUSE_FLOOR::SECOND);
		break;
	}

	return ret;
}

void CTestLevel::ConstructWay(IANApi* pApi, IANEntity* pActor, IANEntity* pTargetDoorEntity, IANEntity* pNextDoorTargetEntity)
{
	float flFloorPosition = GetFloor();

	auto vecActorPosition = pActor->GetOrigin();
	auto vecDoorPosition = pTargetDoorEntity->GetOrigin();

	auto isOnDoorstep = vecActorPosition.x == vecDoorPosition.x;

	if (!isOnDoorstep)
		auto vecMove = pActor->MoveVertical(pApi, Step, flFloorPosition);

	if (vecActorPosition.y != flFloorPosition && !isOnDoorstep)
		return;

	vecActorPosition = pActor->MoveHorizontal(pApi, Step, vecDoorPosition.x);

	if (vecActorPosition.x != vecDoorPosition.x)
		return;

	auto isDoorHorizontal = GetDoorEntityData(pTargetDoorEntity).m_DoorType == DOOR_TYPE::HORIZONTAL;

	if (!isDoorHorizontal)
		vecActorPosition = pActor->MoveVertical(pApi, Step, vecDoorPosition.y);

	if (vecActorPosition.y != vecDoorPosition.y && !isDoorHorizontal)
		return;

	auto vecDestOrigin = pNextDoorTargetEntity->GetOrigin();

	if (isDoorHorizontal)
		vecDestOrigin.y = GetFloor(GetDoorEntityData(pNextDoorTargetEntity).m_LevelFloor);

	pActor->SetOrigin(vecDestOrigin);
}

void CTestLevel::ProcessCurrentRoomMove(IANApi* pApi)
{
	auto woodyOrigin = this->m_pMainActor->GetOrigin();
	auto& woodyData = GetWoodyEntityData(this->m_pMainActor);

	auto vecTarget = woodyData.m_vecMovePt;
	vecTarget.y = GetFloor(woodyData.m_CurrentFloor);

	woodyOrigin = this->m_pMainActor->MoveVertical(pApi, Step, vecTarget.y);

	if (woodyOrigin.y != vecTarget.y)
		return;

	woodyOrigin = this->m_pMainActor->MoveHorizontal(pApi, Step, vecTarget.x);

	if (woodyOrigin.x != vecTarget.x)
		return;

	woodyData.m_ActiveMoveTask = false;
}

void CTestLevel::ProcessMoveActorHallway(IANApi* pApi)
{
	switch (GetWoodyEntityData(this->m_pMainActor).m_CurrentActorRoom)
	{
	case HALLWAY:
		ProcessCurrentRoomMove(pApi);
		break;
	case BATHROOM:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityBathroomHallway, this->m_pDoorEntityHallwayBathroom);
		break;
	case KITCHEN:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityKitchenHallway, this->m_pDoorEntityHallwayKitchen);
		break;
	case HALL:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityHallHallway, this->m_pDoorEntityHallwayHall);
		break;
	}
}

void CTestLevel::ProcessMoveActorBathroom(IANApi* pApi)
{
	switch (GetWoodyEntityData(this->m_pMainActor).m_CurrentActorRoom)
	{
	case HALLWAY:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityHallwayBathroom, this->m_pDoorEntityBathroomHallway);
		break;
	case BATHROOM:
		ProcessCurrentRoomMove(pApi);
		break;
	case KITCHEN:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityKitchenHallway, this->m_pDoorEntityHallwayKitchen);
		break;
	case HALL:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityHallHallway, this->m_pDoorEntityHallwayHall);
		break;
	}
}

void CTestLevel::ProcessMoveActorKitchen(IANApi* pApi)
{
	switch (GetWoodyEntityData(this->m_pMainActor).m_CurrentActorRoom)
	{
	case HALLWAY:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityHallwayKitchen, this->m_pDoorEntityKitchenHallway);
		break;
	case BATHROOM:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityBathroomHallway, this->m_pDoorEntityHallwayBathroom);
		break;
	case KITCHEN:
		ProcessCurrentRoomMove(pApi);
		break;
	case HALL:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityHallKitchen, this->m_pDoorEntityKitchenHall);
		break;
	}
}

void CTestLevel::ProcessMoveActorHall(IANApi* pApi)
{
	switch (GetWoodyEntityData(this->m_pMainActor).m_CurrentActorRoom)
	{
	case HALLWAY:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityHallwayHall, this->m_pDoorEntityHallHallway);
		break;
	case BATHROOM:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityBathroomHallway, this->m_pDoorEntityHallwayBathroom);
		break;
	case KITCHEN:
		ConstructWay(pApi, this->m_pMainActor, this->m_pDoorEntityKitchenHall, this->m_pDoorEntityHallKitchen);
		break;
	case HALL:
		ProcessCurrentRoomMove(pApi);
		break;
	}
}

void CTestLevel::CreateMove(IANApi* pApi)
{
	auto& [currentRoom, moveTask, movePoint, targetRoom, currentFloor] = GetWoodyEntityData(this->m_pMainActor);

	currentRoom = HOUSE_ROOM::ROOM_EMPTY;
	currentFloor = HOUSE_FLOOR::FLOOR_UNK;

	auto groupZone = pApi->FindEntityByGroupID(szWorldEntityClassIDRoomZone);

	for (auto ent = groupZone->First(); *ent != groupZone->Last(); (*ent)++)
	{
		auto entity = ent->Get();
		auto& entityUserData = GetRoomEntityData(entity);

		if (entity->IsWorldPointIntersected(pApi, this->m_pMainActor->GetOrigin()))
		{
			currentRoom = entityUserData.m_HouseRoom;
			currentFloor = entityUserData.m_LevelFloor;
		}

		if (pApi->GetCursorKeyIsReleased(MAIN_FIRST))
		{
			if (!entity->IsScreenPointIntersected(pApi, this->m_pWorld, pApi->GetCursorPos()))
				continue;

			moveTask = true;
			movePoint = pApi->ScreenPointToWorld(this->m_pWorld, pApi->GetCursorPos());
			targetRoom = entityUserData.m_HouseRoom;
		}
	}

	if (moveTask)
	{
		auto actorOrigin = this->m_pMainActor->GetOrigin();

		if (actorOrigin != movePoint)
		{
			switch (targetRoom)
			{
			case HALLWAY:
				ProcessMoveActorHallway(pApi);
				break;
			case BATHROOM:
				ProcessMoveActorBathroom(pApi);
				break;
			case KITCHEN:
				ProcessMoveActorKitchen(pApi);
				break;
			case HALL:
				ProcessMoveActorHall(pApi);
				break;
			}
		}
		else
			moveTask = false;
	}

	auto [dirFlags, speed] = this->m_pMainActor->GetMoveInfo();

	if (dirFlags & ANDirectionMoveFlags::MOVE_UP)
		SetAnimationMoveUp(this->m_pMainActor);

	if (dirFlags & ANDirectionMoveFlags::MOVE_DOWN)
		SetAnimationMoveDown(this->m_pMainActor);

	if (dirFlags & ANDirectionMoveFlags::MOVE_LEFT)
		SetAnimationMoveLeft(this->m_pMainActor);

	if (dirFlags & ANDirectionMoveFlags::MOVE_RIGHT)
		SetAnimationMoveRight(this->m_pMainActor);
}

void CTestLevel::CreateActorEntity(IANApi* pApi, const char* pszActorName)
{
	pApi->RegEntity(&this->m_pMainActor, szWorldEntityPlayer);
	this->m_pMainActor->SetEntityName(pszActorName);
	this->m_pMainActor->SetOrigin(anVec2(1167.f, 615.f)); //326.f;
	this->m_pMainActor->SetUserDataPointer(new ActorWoodyGameData());
}

void CTestLevel::CreateRoomZoneEntity(IANApi* pApi, IANEntity*& pEntity, anVec2 RoomPos, anVec2 RoomSize, HOUSE_ROOM HouseRoom, HOUSE_FLOOR LevelFloor)
{
	pApi->RegEntity(&pEntity, szWorldEntityClassIDRoomZone);
	pEntity->SetOrigin(RoomPos);
	pEntity->SetEntitySize(RoomSize);
	pEntity->SetUserDataPointer(new CRoomZoneEntityData(HouseRoom, LevelFloor));
}

void CTestLevel::CreateDoorEntity(
	IANApi* pApi, 
	IANEntity*& pEntity, 
	const char* pszDoorName, 
	anVec2 Origin, 
	DOOR_TYPE DoorType, 
	HOUSE_ROOM HouseRoom, 
	DOOR_INTERACTIONS DoorInteraction,
	DOOR_INTERACTIONS InvertedDoorInteraction, 
	HOUSE_FLOOR LevelFloor,
	ANAnimationComposition pDoorComposition)
{
	pApi->RegEntity(&pEntity, szWorldEntityClassIDDoor);
	pEntity->SetEntityName(pszDoorName);
	pEntity->SetOrigin(Origin);
	pEntity->SetInteractionController(new DoorEntityInteractionController);
	pEntity->GetAnimCompositionController()->SetAnimationComposition(pDoorComposition);
	pEntity->GetAnimCompositionController()->SetAnimationDuration(0.1f);
	pEntity->SetUserDataPointer(new CDoorEntityData(HouseRoom, DoorType, DoorInteraction, InvertedDoorInteraction, LevelFloor));
}
