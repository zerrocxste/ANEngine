#include "../../includes.h"

const char* pszWorld[] = { "house15.bmp" };
const char* pszWoody[] = { "w_ms2_0004.png", "w_ms2_0005.png", "w_ms2_0006.png" };
const char* pszWoodyLeft[] = { "W_mg3_0000.png", "W_mg3_0001.png", "W_mg3_0002.png", "W_mg3_0003.png", "W_mg3_0004.png", "W_mg3_0005.png", "W_mg3_0006.png", "W_mg3_0007.png" };
const char* pszWoodyRight[] = { "W_mg1_0000.png", "W_mg1_0001.png", "W_mg1_0002.png", "W_mg1_0003.png", "W_mg1_0004.png", "W_mg1_0005.png", "W_mg1_0006.png", "W_mg1_0007.png" };
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
	"W_leave_0009.png", };
const char* pszDoorAnim[] = { "N_leave_0000.png" };

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
	pApi->CreateAnimationComposition(pszDoorAnim, 1, &this->m_DoorComposition);

	pApi->RegWorld(&this->m_pWorld);
	this->m_pWorld->SetWorldSize(pApi->GetImageSize(pApi->GetAnimationCompositionFrameFromID(this->m_WorldComposition, 0)));
	this->m_pWorld->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_WorldComposition);

	pApi->RegEntity(&this->m_pMainActor, "CLASSID_Player");
	this->m_pMainActor->SetOrigin(this->m_pWorld->GetMetrics().m_WorldSize * 0.5f);

	pApi->RegEntity(&this->m_pDoorEntityHallwayKitchen, "CLASSID_WorldEntity");
	this->m_pDoorEntityHallwayKitchen->SetOrigin(anVec2(1111.f, 550.f));

	this->m_pDoorEntityHallwayKitchen->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_DoorComposition);
	this->m_pDoorEntityHallwayKitchen->m_pIANAnimationCompositionController->SetAnimationDuration(0.1f);

	pApi->RegEntity(&this->m_pDoorEntityHallwayHall, "CLASSID_WorldEntity");
	this->m_pDoorEntityHallwayHall->SetOrigin(anVec2(500.f, 550.f));
	
	this->m_pDoorEntityHallwayHall->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_DoorComposition);
	this->m_pDoorEntityHallwayHall->m_pIANAnimationCompositionController->SetAnimationDuration(0.1f);
}

void CTestLevel::OnUnloadScene(IANApi* pApi)
{
	pApi->DeleteAnimationComposition(&this->m_WorldComposition);
	pApi->DeleteAnimationComposition(&this->m_DoorComposition);
	pApi->DeleteAnimationComposition(&this->m_WoodyComposition);
	pApi->DeleteAnimationComposition(&this->m_WoodyCompositionLeft);
	pApi->DeleteAnimationComposition(&this->m_WoodyCompositionRight);
	
	pApi->UnregWorld(&this->m_pWorld);

	pApi->UnregEntity(&this->m_pMainActor);
}

void CTestLevel::Entry(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	this->m_pMainActor->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_WoodyComposition);
	this->m_pMainActor->m_pIANAnimationCompositionController->SetAnimationDuration(0.3f);

	float Step = 250.f;
	if (pApi->GetKeyIsDowned('W'))
		this->m_pMainActor->MoveUp(pApi, Step);
	if (pApi->GetKeyIsDowned('S'))
		this->m_pMainActor->MoveDown(pApi, Step);
	if (pApi->GetKeyIsDowned('A'))
	{
		this->m_pMainActor->MoveLeft(pApi, Step);
		this->m_pMainActor->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_WoodyCompositionLeft);
		this->m_pMainActor->m_pIANAnimationCompositionController->SetAnimationDuration(0.1f);
	}
	if (pApi->GetKeyIsDowned('D'))
	{
		this->m_pMainActor->MoveRight(pApi, Step);
		this->m_pMainActor->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_WoodyCompositionRight);
		this->m_pMainActor->m_pIANAnimationCompositionController->SetAnimationDuration(0.1f);
	}

	if (pApi->GetKeyIsDowned('F'))
		this->m_pDoorEntityHallwayKitchen->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_WoodyDoorLeave);
	else
		this->m_pDoorEntityHallwayKitchen->m_pIANAnimationCompositionController->SetAnimationComposition(this->m_DoorComposition);

	if (pApi->GetCursorKeyIsDowned(CursorKey::MAIN_SECOND))
		this->m_pMainActor->MovePoint(pApi, Step, this->m_pDoorEntityHallwayHall->GetOrigin());

	this->m_pWorld->SetZoom(this->m_WorldZoom);
	this->m_pWorld->SetCameraToEntity(this->m_pMainActor);
	this->m_pWorld->Update(pApi);
	this->m_pWorld->Draw(pApi);

	//if (this->m_pDoorEntityHallwayHall->IsScreenPointIntersected(pApi, this->m_pWorld, pApi->GetCursorPos()))


	pApi->FindEntityByGroupID("CLASSID_WorldEntity")->Draw(pApi, this->m_pWorld);
	pApi->FindEntityByGroupID("CLASSID_Player")->Draw(pApi, this->m_pWorld);

	auto WorldMetrics = this->m_pWorld->GetMetrics();
	auto ActorScreen = pApi->WorldToScreen(this->m_pWorld, this->m_pMainActor);
	char buff[512] = { 0 };
	sprintf_s(buff, "FPS: %d\n"
		"Frametime: %lf\n"
		"Screen size: %.1f:%.1f\n"
		"World Size: %.1f:%.1f\n"
		"World pos: %.1f:%.1f\n"
		"World screen size: %.1f:%.1f\n"
		"Camera world: %.1f:%.1f\n"
		"Camera screen: %.1f:%.1f\n"
		"Actor world: %f:%f\n"
		"Actor screen: %.1f:%.1f",
		pApi->FPS,
		pApi->Frametime,
		ScreenSize.x, ScreenSize.y,
		WorldMetrics.m_WorldSize.x, WorldMetrics.m_WorldSize.y,
		WorldMetrics.m_WorldScreenPos.x, WorldMetrics.m_WorldScreenPos.y,
		WorldMetrics.m_WorldScreenSize.x, WorldMetrics.m_WorldScreenSize.y,
		WorldMetrics.m_CameraWorld.x, WorldMetrics.m_CameraWorld.y,
		WorldMetrics.m_CameraScreen.x, WorldMetrics.m_CameraScreen.y,
		this->m_pMainActor->GetOrigin().x, this->m_pMainActor->GetOrigin().y,
		ActorScreen.x, ActorScreen.y);
	pApi->TextDraw(buff, anVec2(10.f, 20.f), anColor::White());

	if (pApi->AddButton("Go to menu", anVec2(ScreenSize.x - 130.f - 5.f, ScreenSize.y - 50.f - 5.f), anVec2(130.f, 50.f)))
		pApi->ConnectToScene(new CTestGameScene());

	pApi->DrawLine(anVec2(ScreenSize.x * 0.5f, 0.f), anVec2(ScreenSize.x * 0.5f, ScreenSize.y), anColor::White(), 5.f);
	pApi->DrawLine(anVec2(0.f, ScreenSize.y * 0.5f), anVec2(ScreenSize.x, ScreenSize.y * 0.5f), anColor::White(), 5.f);

	pApi->PushFontColor(anColor::White());
	pApi->AddSliderFloat("Map zoom", anVec2(10.f, ScreenSize.y - 70.f), anVec2(300.f, 30.f), 0.f, 10000.f, &this->m_WorldZoom);
	pApi->PopFontColor();
}
