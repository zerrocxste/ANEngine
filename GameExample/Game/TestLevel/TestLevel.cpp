#include "../../includes.h"

CTestLevel::CTestLevel()
{
	this->m_WorldZoom = 700.f;
}

CTestLevel::~CTestLevel()
{

}

void CTestLevel::OnLoadScene(IANApi* pApi)
{
	pApi->CreateImage("XMHf4PJ.jpg", &this->LevelBG);

	pApi->RegWorld(&this->m_pWorld);

	this->m_pWorld->SetWorldSize(pApi->GetImageSize(this->LevelBG));

	pApi->RegEntity(&this->m_pMainActor);

	pApi->RegGuiWindow(&this->m_GuiWindow, anVec2(500.f));
}

void CTestLevel::OnUnloadScene(IANApi* pApi)
{
	pApi->FreeImage(&this->LevelBG);

	pApi->UnregWorld(&this->m_pWorld);

	pApi->UnregEntity(&this->m_pMainActor);
}

void CTestLevel::Entry(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	float Step = 0.3f;
	if (pApi->GetKeyIsDowned('W'))
		this->m_pMainActor->MoveUp(pApi, 300.f);
	if (pApi->GetKeyIsDowned('S'))
		this->m_pMainActor->MoveDown(pApi, 300.f);
	if (pApi->GetKeyIsDowned('A'))
		this->m_pMainActor->MoveLeft(pApi, 300.f);
	if (pApi->GetKeyIsDowned('D'))
		this->m_pMainActor->MoveRight(pApi, 300.f);

	this->m_pWorld->SetZoom(this->m_WorldZoom);
		
	this->m_pWorld->SetCameraToEntity(this->m_pMainActor);

	

	this->m_pWorld->Draw(pApi, this->LevelBG);

	this->m_pWorld->Update(pApi);

	auto ActorScreen = pApi->WorldToScreen(this->m_pWorld, this->m_pMainActor);

	pApi->DrawRectangle(ActorScreen, anVec2(50.f, 50.f), anColor::Red(), 50.f, 1.f, true);

	auto WorldMetrics = this->m_pWorld->GetMetrics();

	char buff[512] = { 0 };
	sprintf_s(buff, "FPS: %d\nFrametime: %lf\nScreen size: %.1f:%.1f\nWorld Size: %.1f:%.1f\nWorld pos: %.1f:%.1f\nWorld screen size: %.1f:%.1f\nCamera world: %.1f:%.1f\nCamera screen: %.1f:%.1f\nActor world: %f:%f\nActor screen: %.1f:%.1f",
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

	pApi->AddSliderFloat("Map zoom", anVec2(10.f, ScreenSize.y - 70.f), anVec2(300.f, 30.f), -1000.f, 1000.f, &this->m_WorldZoom);

	pApi->PopFontColor();
}
