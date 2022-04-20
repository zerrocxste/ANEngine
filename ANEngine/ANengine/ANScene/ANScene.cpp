#include "../ANEngine.h"

ANScene::ANScene(ANCore* pCore) :
	IANError(),
	m_pCore(pCore)
{

}

ANScene::~ANScene()
{

}

bool ANScene::Run()
{
	auto w = this->m_pCore->GetWindow();

	if (!w->MakeWindow())
	{
		this->SetError("%s() -> Error make window\n%s", __FUNCTION__, w->What());
		return false;
	}

	auto r = this->m_pCore->GetRenderer();

	if (!r->Initalize())
	{
		this->SetError("%s() -> Error initialize renderer\n%s", __FUNCTION__, r->What());
		return false;
	}

	//r->SetMaxFps(60);

	ANFontID fontStolzLight;

	if (!r->CreateFontFromFile("StolzLight.ttf", 72.f, &fontStolzLight))
	{
		this->SetError("%s() -> Error loading font", __FUNCTION__);
		return false;
	}

	ANFontID fontArial;

	if (!r->CreateFontFromFile("C:\\Windows\\Fonts\\Tahoma.ttf", 32.f, &fontArial))
	{
		this->SetError("%s() -> Error loading font", __FUNCTION__);
		return false;
	}

	ANImageID imageKrolik;

	ANUniqueResource resImageKrolik;

	auto rm = this->m_pCore->GetResourceManager();

	if (!rm->ReadBinFile("Krolik.png", &resImageKrolik))
	{
		this->SetError("%s() -> Error loading image", __FUNCTION__);
		return false;
	}

	if (!r->CreateImageFromResource(&resImageKrolik, &imageKrolik))
	{
		this->SetError("%s() -> Error create image", __FUNCTION__);
		return false;
	}

	resImageKrolik.Free();

	auto s = this->m_pCore->GetScriptManager();

	if (!s->InitScripts())
	{
		this->SetError("%s() -> Error initialize scripts\n%s", __FUNCTION__, s->What());
		return false;
	}

	w->WindowShow();

	while (w->ProcessWindow())
	{
		if (!w->IsAllowRender())
			continue;

		if (!r->PrepareScene())
			continue;

		if (!r->BeginFrame())
		{
			this->SetError("%s() -> Begin frame issue", __FUNCTION__);
			return false;
		}

		r->ClearScene();

		

		auto ScreenSize = r->GetScreenSize();
		r->DrawImage(imageKrolik, anVec2(0.f, 0.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);
		r->DrawImage(imageKrolik, anVec2(ScreenSize.x / 2.f, 0.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);
		r->DrawImage(imageKrolik, anVec2(0.f, ScreenSize.y / 2.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);
		r->DrawImage(imageKrolik, anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), anVec2(ScreenSize.x / 2.f, ScreenSize.y / 2.f), 0.5f);

		char buff[128] = { 0 };
		sprintf_s(buff, "FPS: %d Frametime: %lf", r->GetFramePerSecond(), r->GetFrameTime());
		r->TextDraw(buff, anVec2(10.f, 10.f), anColor(255, 0, 0, 255), fontArial);

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
