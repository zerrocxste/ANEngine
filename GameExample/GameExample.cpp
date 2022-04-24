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
}

void CTestGameScene::OnUnloadScene(IANApi* pApi)
{
	pApi->FreeFont(&this->m_fontStolzLight);
	pApi->FreeImage(&this->m_imgImageKrolik);

	if (this)
		delete this;
}

void CTestGameScene::Entry(IANApi* pApi)
{
	pApi->DrawImage(this->m_imgImageKrolik, anVec2(), pApi->ScreenSize, 0.5f);

	char buff[256] = { 0 };
	sprintf_s(buff, "FPS: %d\nFrametime: %lf\nScreenSize: %.0f:%.0f", pApi->FPS, pApi->Frametime, pApi->ScreenSize.x, pApi->ScreenSize.y);
	pApi->TextDraw(buff, anVec2(30.f, 30.f), anColor::Red(), this->m_fontStolzLight);

	/*pApi->DrawCircle(anVec2(100.f, 100.f), anColor::Blue(), 100.f, 5.f);
	pApi->DrawRectangle(anVec2(200.f, 200.f), anVec2(100.f, 100.f), anColor::Green(), 15.f, 25.f);
	pApi->DrawTrinagle(anVec2(350.f, 350.f), anVec2(400.f, 350.f), anVec2(375.f, 450.f), anColor::Magenta(), 15.f);
	pApi->DrawLine(anVec2(), pApi->ScreenSize, anColor::Yellow());*/

	static bool bVar = false;
	pApi->AddCheckbox("Test", &bVar);
}

int main()
{
	auto Loader = CreateEngineInstance(RenderTypes::D2D, "GameExample", anVec2(100.f, 100.f), anVec2(700.f, 500.f), true);

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