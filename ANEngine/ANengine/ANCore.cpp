#include "ANEngine.h"

ANCore::ANCore(
	RenderTypes RenderType, 
	const char* pszWindowName,
	anVec2 vWindowPosition, 
	anVec2 vWindowSize, 
	bool bHasWindowFrame,
	const char* pszPathMainScriptEntry)
{
	m_EngineComponents.m_pANWindow = ANMemory::GetInstance()->Allocate<ANWindow>(this, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame);
	m_EngineComponents.m_pANInput = ANMemory::GetInstance()->Allocate<ANInput>(this);
	m_EngineComponents.m_ANRenderer = ANMemory::GetInstance()->Allocate<ANRenderer>(this, RenderType);
	m_EngineComponents.m_pANGame = ANMemory::GetInstance()->Allocate<ANGame>(this);
	m_EngineComponents.m_pANResourceManager = ANMemory::GetInstance()->Allocate<ANResourceManager>();
	m_EngineComponents.m_pANScriptManager = ANMemory::GetInstance()->Allocate<ANScriptManager>(this, pszPathMainScriptEntry);
}

ANCore::~ANCore()
{

}

bool ANCore::Initialize()
{
	
}

ANWindow* ANCore::GetWindow()
{
	assert(this->m_EngineComponents.m_pANWindow != nullptr);
	return this->m_EngineComponents.m_pANWindow;
}

ANInput* ANCore::GetInput()
{
	assert(this->m_EngineComponents.m_pANInput != nullptr);
	return this->m_EngineComponents.m_pANInput;
}

ANRenderer* ANCore::GetRenderer()
{
	assert(this->m_EngineComponents.m_ANRenderer != nullptr);
	return this->m_EngineComponents.m_ANRenderer;
}

ANGame* ANCore::GetGame()
{
	assert(this->m_EngineComponents.m_pANGame != nullptr);
	return this->m_EngineComponents.m_pANGame;
}

ANResourceManager* ANCore::GetResourceManager()
{
	assert(this->m_EngineComponents.m_pANResourceManager != nullptr);
	return this->m_EngineComponents.m_pANResourceManager;
}

ANScriptManager* ANCore::GetScriptManager()
{
	assert(this->m_EngineComponents.m_pANScriptManager != nullptr);
	return this->m_EngineComponents.m_pANScriptManager;
}

ANScriptInterpreter* ANCore::GetScriptInterpreter()
{
	assert(this->m_EngineComponents.m_pANScriptInterpreter != nullptr);
	return this->m_EngineComponents.m_pANScriptInterpreter;
}

bool ANCore::Run()
{
	auto w = GetWindow();

	if (!w->MakeWindow())
	{
		MessageBox(0, w->What(), "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	auto r = GetRenderer();

	if (!r->Initalize())
	{
		MessageBox(0, r->What(), "Error", MB_ICONERROR | MB_OK);
		return false;
	}
	
	ANFontID fontStolzLight;
	
	if (!r->CreateFontFromFile("StolzLight.ttf", 72.f, &fontStolzLight))
	{
		MessageBox(0, "Error loading font", "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	ANFontID fontArial;

	if (!r->CreateFontFromFile("C:\\Windows\\Fonts\\Tahoma.ttf", 72.f, &fontArial))
	{
		MessageBox(0, "Error loading font", "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	ANImageID imageKrolik;

	ANUniqueResource resImageKrolik;

	auto rm = GetResourceManager();

	if (!rm->ReadBinFile("Krolik.png", &resImageKrolik))
	{
		MessageBox(0, "Error loading image", "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	if (!r->CreateImageFromResource(&resImageKrolik, &imageKrolik))
	{
		MessageBox(0, "Error create image", "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	resImageKrolik.Free();

	auto s = GetScriptManager();

	if (!s->ProcessScripts())
	{
		MessageBox(0, s->What(), "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	w->WindowShow();

	while (w->ProcessWindow())
	{
		if (!w->IsAllowRender())
			continue;

		r->BeginFrame();

		auto ScreenSize = r->GetScreenSize();

		r->DrawImage(imageKrolik, anVec2(0.f, 0.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);
		r->DrawImage(imageKrolik, anVec2(ScreenSize.x / 2.f, 0.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);
		r->DrawImage(imageKrolik, anVec2(0.f, ScreenSize.y / 2.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);
		r->DrawImage(imageKrolik, anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);

		r->TextDraw("FPS: ", anVec2(10.f, 10.f), anColor(255, 0, 0, 255), fontArial);

		r->TextDraw(u8"Тестовый текст, Hello!", anVec2(50.f, 50.f), anColor::Green(), fontStolzLight);

		auto Size = anVec2(50.f, 50.f);
		r->DrawRectangle(anVec2(50.f, 200.f), Size, anColor::Green());
		r->DrawFilledRectangle(anVec2(50.f, 300.f), Size, anColor(255, 150, 0, 150), 30.f);
		r->DrawCircle(anVec2(50.f, 400.f), anColor::Blue(), 50.f);
		r->DrawFilledCircle(anVec2(50.f, 500.f), anColor::Magenta(), 50.f);

		r->EndFrame();
	}

	return true;
}
