#include "../../includes.h"

CTestCheckboxSkin::CTestCheckboxSkin(ANImageID bgImage, ANImageID markImage) :
	m_bgImage(bgImage),
	m_markImage(markImage)
{

}

CTestCheckboxSkin::~CTestCheckboxSkin()
{

}

void CTestCheckboxSkin::SetSkin(bool IsHovered, bool IsPressed, bool IsClicked, anRect* pBgRect, anColor* pBgColor, ANImageID* pBgImage, anRect* pMarkRect, anColor* pMarkColor, ANImageID* pMarkImage)
{
	*pBgImage = this->m_bgImage;
}


CTestSliderSkin::CTestSliderSkin(ANImageID bgImage, ANImageID sliderImage) :
	m_bgImage(bgImage),
	m_sliderImage(sliderImage)
{

}

CTestSliderSkin::~CTestSliderSkin()
{

}

void CTestSliderSkin::SetSkin(bool IsHovered, bool IsPressed, bool IsClicked, anRect* pBgRect, anColor* pBgColor, ANImageID* pBgImage, anRect* pSliderRect, anColor* pSliderColor, ANImageID* sliderImage)
{
	*pBgImage = this->m_bgImage;
	*sliderImage = this->m_sliderImage;
}

CTestGameScene::CTestGameScene() :
	m_imgImageKrolik(0),
	m_fontStolzLight(0),
	m_AnotherWindow(0)
{
	
}

CTestGameScene::~CTestGameScene()
{

}

void CTestGameScene::OnLoadScene(IANApi* pApi)
{
	pApi->CreateFontFromFile("StolzLight.ttf", 25.f, &this->m_fontStolzLight);
	pApi->CreateImage("Krolik.png", &this->m_imgImageKrolik, true);
	pApi->RegGuiWindow(&this->m_AnotherWindow, anVec2(300.f, 200.f));

	m_pTestCheckboxSkin = (IANCheckboxSkin*)new CTestCheckboxSkin(this->m_imgImageKrolik, this->m_imgImageKrolik);
	m_pSliderSkin = (IANSliderSkin*)new CTestSliderSkin(this->m_imgImageKrolik, this->m_imgImageKrolik);
}

void CTestGameScene::OnUnloadScene(IANApi* pApi)
{
	pApi->ClearAndDeleteLinkedImages();
	pApi->ClearAndDeleteLinkedAnimationCompositions();
	pApi->FreeFont(&this->m_fontStolzLight);
	pApi->UnregGuiWindow(&this->m_AnotherWindow);

	delete m_pTestCheckboxSkin;
	delete m_pSliderSkin;

	if (this)
		delete this;
}

void CTestGameScene::Entry(IANApi* pApi)
{
	auto ScreenSize = pApi->GetScreenSize();

	pApi->DrawImage(this->m_imgImageKrolik, anVec2(), ScreenSize, 0.5f);

	char buff[256] = { 0 };
	sprintf_s(buff, "FPS: %.1f\nFrametime: %lf\nScreenSize: %.0f:%.0f", pApi->FPS, pApi->Frametime, ScreenSize.x, ScreenSize.y);
	pApi->TextDraw(buff, anVec2(5.f, 5.f), anColor::White());

	pApi->TextDraw("TEST", anVec2(40.f, 320.f), anColor::Red());

	static bool bVar = false;
	pApi->AddCheckbox((const char*)u8"Тест", anVec2(30.f, 130.f), anVec2(30.f, 30.f), &bVar, this->m_pTestCheckboxSkin);

	static int iVar = 24;
	pApi->AddSliderInt("Test slider", anVec2(30.f, 180.f), anVec2(250.f, 30.f), 10, 68, &iVar);

	static float flVar = 228.f;
	pApi->AddSliderFloat("Test slider float", anVec2(30.f, 230.f), anVec2(250.f, 30.f), 130.f, 440.f, &flVar, this->m_pSliderSkin);

	pApi->DrawRectangle(anVec2(30.f, 320.f), anVec2(100.f, 30.f), anColor::White(), 1.f, 0.f, true);

	pApi->PushFont(this->m_fontStolzLight);

	pApi->TextDraw("TEST", anVec2(40.f, 320.f), anColor::Red());

	if (pApi->BeginGuiWindow(this->m_AnotherWindow, anVec2(30.f, 400.f)))
	{
		anVec2 WindowSize = pApi->GetGuiWindowSize(this->m_AnotherWindow);

		if (pApi->GetKeyIsReleased('V'))
			pApi->ResizeGuiWindow(&this->m_AnotherWindow, anVec2(500.f, 500.f));

		pApi->DrawRectangle(anVec2(), WindowSize, anColor::Blue(), 0.f, 0.f, true);

		//pApi->DrawImage(this->m_imgImageKrolik, anVec2(), WindowSize, 0.5f);
		pApi->DrawRectangle(anVec2(), anVec2(WindowSize.x, 30.f), anColor::Red(), 0.f, 0.f, true);
		pApi->TextDraw("New window", anVec2(10.f, 0.f), anColor::Black());

		pApi->AddSliderInt("Test slider", anVec2(10.f, 35.f), anVec2(250.f, 30.f), 10, 68, &iVar);

		pApi->TextDraw("TEST", anVec2(10.f, 120.f), anColor::Red());
		pApi->TextDraw("TEST2", anVec2(10.f, 150.f), anColor::Red());
		pApi->TextDraw("TEST3", anVec2(10.f, 180.f), anColor::Red());
		pApi->TextDraw("TEST3", anVec2(10.f, 210.f), anColor::Red());

		pApi->EndGuiWindow();
	}

	pApi->PopFont();

	if (pApi->AddButton("Run test level", anVec2(400.f, 500.f), anVec2(150.f, 50.f)))
		pApi->ConnectToScene(new CTestLevel());

	anVec2 SizeQuitButton(150.f, 50.f);
	if (pApi->AddButton("Quit", ScreenSize - SizeQuitButton - anVec2(10.f), SizeQuitButton))
		pApi->LeaveApp();
}
