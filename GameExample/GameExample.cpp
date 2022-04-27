#include <iostream>

#include "../ANSDK/ANSDK/ANSDK.h"

class CTestGameScene : public IANGameScene
{
public:
	CTestGameScene();
	~CTestGameScene();

	void OnLoadScene(IANApi* pApi) override;
	void OnUnloadScene(IANApi* pApi) override;
	void Entry(IANApi* pApi) override;

private:
	ANImageID m_imgImageKrolik;
	ANFontID m_fontStolzLight;
	ANGuiWindowID m_AnotherWindow;
};

CTestGameScene::CTestGameScene() : 
	m_imgImageKrolik(0),
	m_fontStolzLight(0)
{

}

CTestGameScene::~CTestGameScene()
{

}

void CTestGameScene::OnLoadScene(IANApi* pApi)
{
	pApi->CreateFontFromFile("StolzLight.ttf", 25.f, &this->m_fontStolzLight);
	pApi->CreateImage("Krolik.png", &this->m_imgImageKrolik);
	pApi->RegGuiWindow(&this->m_AnotherWindow, anVec2(300.f, 200.f));
}

void CTestGameScene::OnUnloadScene(IANApi* pApi)
{
	pApi->FreeFont(&this->m_fontStolzLight);
	pApi->FreeImage(&this->m_imgImageKrolik);
	pApi->UnregGuiWindow(&this->m_AnotherWindow);

	if (this)
		delete this;
}

void CTestGameScene::Entry(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	pApi->DrawImage(this->m_imgImageKrolik, anVec2(), pApi->GetScreenSize(), 0.5f);

	char buff[256] = { 0 };
	sprintf_s(buff, "FPS: %d\nFrametime: %lf\nScreenSize: %.0f:%.0f", pApi->FPS, pApi->Frametime, ScreenSize.x, ScreenSize.y);
	pApi->TextDraw(buff, anVec2(5.f, 5.f), anColor::Red());

	static bool bVar = false;
	pApi->AddCheckbox("Test", anVec2(30.f, 130.f), anVec2(30.f, 30.f), &bVar);

	static int iVar = 24;
	pApi->AddSliderInt("Test slider", anVec2(30.f, 180.f), anVec2(250.f, 30.f), 10, 68, &iVar);

	static float flVar = 228.f;
	pApi->AddSliderFloat("Test slider float", anVec2(30.f, 230.f), anVec2(250.f, 30.f), 130.f, 440.f, &flVar);

	pApi->DrawRectangle(anVec2(30.f, 320.f), anVec2(100.f, 30.f), anColor::White(), 1.f, 0.f, true);
	
	pApi->PushFont(this->m_fontStolzLight);

	pApi->TextDraw("TEST", anVec2(40.f, 320.f), anColor::Red());

	pApi->BeginGuiWindow(this->m_AnotherWindow, anVec2(30.f, 400.f));
	pApi->DrawImage(this->m_imgImageKrolik, anVec2(), pApi->GetCurrentWindowSize(), 0.5f);
	pApi->AddSliderInt("Test slider", anVec2(10.f, 10.f), anVec2(250.f, 30.f), 10, 68, &iVar);
	pApi->TextDraw("TEST", anVec2(10.f, 90.f), anColor::Red());
	pApi->TextDraw("TES2", anVec2(10.f, 130.f), anColor::Red());
	pApi->EndGuiWindow();

	pApi->PopFont();
}

int main()
{
	auto Loader = CreateEngineInstance(RenderTypes::D2D, "GameExample", anVec2(100.f, 100.f), anVec2(700.f, 700.f), true);

	if (!Loader->InitializeLoader())
	{
		MessageBox(0, Loader->What(), "Error", MB_ICONERROR);
		return 1;
	}

	Loader->ConnectScene(new CTestGameScene());

	if (!Loader->RunScene())
	{
		MessageBox(0, Loader->What(), "Error", MB_ICONERROR);
		return 1;
	}

	return 0;
}