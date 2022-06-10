#include "../../includes.h"

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

DoorEntityInteractionController::DoorEntityInteractionController() : 
	m_bNextDoor(false)
{

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

	if (!strcmp(pszEventClassID, "CLASSID_EVENT_Door"))
	{
		if (!pApi->GetInteractionMessagesList()->IsEventCanceledByClassID("CLASSID_EVENT_Door", pThisEntity))
			return false;

		auto& pActorEntity = *ppRemoteEntity;

		IANEntity* DestEntity = nullptr;

		if (!strcmp(pszEventMessage, "EVENT_DoorTransitionHallwayKitchen"))
			DestEntity = pTestLevel->m_pDoorEntityKitchenHallway;
		else if (!strcmp(pszEventMessage, "EVENT_DoorTransitionKitchenHallway"))
			DestEntity = pTestLevel->m_pDoorEntityHallwayKitchen;
		else if (!strcmp(pszEventMessage, "EVENT_DoorTransitionHallwayHall"))
			DestEntity = pTestLevel->m_pDoorEntityHallHallway;
		else if (!strcmp(pszEventMessage, "EVENT_DoorTransitionHallHallway"))
			DestEntity = pTestLevel->m_pDoorEntityHallwayHall;

		if (!DestEntity)
			return true;

		if (!bNeedCancelEvent)
		{
			auto OnTarget = this->m_bNextDoor;

			if (!OnTarget)
				OnTarget = pActorEntity->MovePoint(pApi, 250.f, pThisEntity->GetOrigin()) == pThisEntity->GetOrigin();

			if (OnTarget)
			{
				pActorEntity->SetVisible(false);

				pThisEntity->m_pAnimCompositionController->PlayAnimation(pTestLevel->m_WoodyDoorLeave, true);

				if (pThisEntity->m_pAnimCompositionController->IsAnimationCycleComplete())
				{
					pActorEntity->SetOrigin(DestEntity->GetOrigin());
					DestEntity->m_pAnimCompositionController->PlayAnimation(pTestLevel->m_WoodyDoorEnter, true);
					this->m_bNextDoor = true;
				}

				if (this->m_bNextDoor && DestEntity->m_pAnimCompositionController->IsAnimationCycleComplete())
				{
					pThisEntity->m_pAnimCompositionController->UnlockPlayingAnimationState();
					DestEntity->m_pAnimCompositionController->UnlockPlayingAnimationState();
					pActorEntity->SetVisible(true);
					this->m_bNextDoor = false;
					return true;
				}
			}
		}
		else
		{
			if (this->m_bNextDoor || pActorEntity->GetOrigin() == pThisEntity->GetOrigin())
			{
				pThisEntity->m_pAnimCompositionController->UnlockPlayingAnimationState();
				pThisEntity->m_pAnimCompositionController->StopRunningAnimation();
				DestEntity->m_pAnimCompositionController->UnlockPlayingAnimationState();
				DestEntity->m_pAnimCompositionController->StopRunningAnimation();
				pActorEntity->SetVisible(true);
				this->m_bNextDoor = false;
			}
			return true;
		}
	}

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
	auto ScreenSize = pApi->GetScreenSize();

	this->m_pMainActor->m_pAnimCompositionController->SetAnimationComposition(this->m_WoodyComposition);
	this->m_pMainActor->m_pAnimCompositionController->SetAnimationDuration(0.3f);

	float Step = 250.f;
	if (pApi->GetKeyIsDowned('W'))
		this->m_pMainActor->MoveUp(pApi, Step);
	if (pApi->GetKeyIsDowned('S'))
		this->m_pMainActor->MoveDown(pApi, Step);
	if (pApi->GetKeyIsDowned('A'))
	{
		this->m_pMainActor->MoveLeft(pApi, Step);
		this->m_pMainActor->m_pAnimCompositionController->SetAnimationComposition(this->m_WoodyCompositionLeft);
		this->m_pMainActor->m_pAnimCompositionController->SetAnimationDuration(0.1f);
	}
	if (pApi->GetKeyIsDowned('D'))
	{
		this->m_pMainActor->MoveRight(pApi, Step);
		this->m_pMainActor->m_pAnimCompositionController->SetAnimationComposition(this->m_WoodyCompositionRight);
		this->m_pMainActor->m_pAnimCompositionController->SetAnimationDuration(0.1f);
	}

	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallwayKitchen, "EVENT_DoorTransitionHallwayKitchen");
	ProcessDoorInteraction(pApi, this->m_pDoorEntityKitchenHallway, "EVENT_DoorTransitionKitchenHallway");
	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallwayHall, "EVENT_DoorTransitionHallwayHall");
	ProcessDoorInteraction(pApi, this->m_pDoorEntityHallHallway, "EVENT_DoorTransitionHallHallway");

	this->m_pWorld->SetZoom(this->m_WorldZoom);
	this->m_pWorld->SetCameraToEntity(this->m_pMainActor);
	this->m_pWorld->Update(pApi);
	this->m_pWorld->Draw(pApi);

	pApi->FindEntityByGroupID("CLASSID_WorldEntity")->Update(pApi).Draw(pApi, this->m_pWorld);
	pApi->FindEntityByGroupID("CLASSID_Player")->SortByYOrder().Update(pApi).Draw(pApi, this->m_pWorld);

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

	if (pApi->AddButton("Go to menu", anVec2(ScreenSize.x - 130.f - 5.f, ScreenSize.y - 50.f - 5.f), anVec2(130.f, 50.f)))
		pApi->ConnectToScene(new CTestGameScene());

	pApi->DrawLine(anVec2(ScreenSize.x * 0.5f, 0.f), anVec2(ScreenSize.x * 0.5f, ScreenSize.y), anColor::White(), 5.f);
	pApi->DrawLine(anVec2(0.f, ScreenSize.y * 0.5f), anVec2(ScreenSize.x, ScreenSize.y * 0.5f), anColor::White(), 5.f);

	pApi->PushFontColor(anColor::White());
	pApi->AddSliderFloat("Map zoom", anVec2(10.f, ScreenSize.y - 70.f), anVec2(300.f, 30.f), 0.f, 10000.f, &this->m_WorldZoom);
	pApi->PopFontColor();
}

void CTestLevel::ProcessDoorInteraction(IANApi* pApi, IANEntity*& ppEntity, const char* pszEventName)
{
	if (ppEntity->IsScreenPointIntersected(pApi, this->m_pWorld, pApi->GetCursorPos()) && pApi->GetCursorKeyIsReleased(CursorKey::MAIN_FIRST))
	{
		auto szDoorIntercationClassID = "CLASSID_EVENT_Door";

		pApi->GetInteractionMessagesList()->SendCancelInteractionMessageForClassID(szDoorIntercationClassID);

		pApi->GetInteractionMessagesList()->AddInteractionMessageForEntityName(szDoorIntercationClassID, 
			pszEventName,
			ppEntity->GetEntityName(),
			&this->m_pMainActor, 
			this);
	}
}

void CTestLevel::CreateDoorEntity(IANApi* pApi, IANEntity*& ppEntity, const char* pszDoorName, anVec2 Origin)
{
	pApi->RegEntity(&ppEntity, "CLASSID_WorldEntity");
	ppEntity->SetEntityName(pszDoorName);
	ppEntity->SetOrigin(Origin);
	ppEntity->SetInteractionController(new DoorEntityInteractionController);
	ppEntity->m_pAnimCompositionController->SetAnimationComposition(this->m_DoorComposition);
	ppEntity->m_pAnimCompositionController->SetAnimationDuration(0.1f);
}
