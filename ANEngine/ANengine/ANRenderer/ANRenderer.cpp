#include "../ANEngine.h"

ANRenderer::ANRenderer(ANCore* pCore, bool bVerticalSync) :
	m_pCore(pCore),
	m_bEnableVerticalSync(bVerticalSync),
	m_Window(0),
	m_CurrentWindowID(0), 
	m_CurrentWindowIDPos(anVec2()),
	m_CurrentWindowIDSize(anVec2()),
	m_FontIDDefault(0),
	m_FontID(0),
	m_FontAppierence(FontAppierence::FONT_NONE)
{
	
}

ANRenderer::~ANRenderer()
{

}

bool ANRenderer::Initalize()
{
	this->m_Window = this->m_pCore->GetPlatform()->GetWindowHandle();

	if (!CreateBackendRender())
		return false;

	if (!CreateDefaultFont())
		return false;

	return true;
}

bool ANRenderer::CreateBackendRender()
{
#ifdef BACKEND_DIRECT2D
	this->m_pRendererBackend = ANMemory::GetInstance()->Allocate<ANRendererlatformD2D>();
#endif // BACKEND_DIRECT2D

	if (!this->m_pRendererBackend->InitializeRenderer(this->m_Window, this->m_bEnableVerticalSync, nullptr))
	{
		this->SetError(__FUNCTION__ " > Error initialize render\n%s", this->m_pRendererBackend->What());
		return false;
	}

	return true;
}

bool ANRenderer::CreateDefaultFont()
{
	const char* pszDefaultFont = "C:\\Windows\\Fonts\\Arial.ttf";

	if (!CreateFontFromFile(pszDefaultFont, 20.f, &this->m_FontIDDefault))
	{
		this->SetError(__FUNCTION__ " -> Error load default font '%s'", pszDefaultFont);
		return false;
	}

	return true;
}

bool ANRenderer::CheckObjectIsGuiWindowScoped(anVec2 Pos)
{
	return this->m_CurrentWindowIDRect.IsIntersected(Pos);
}

bool ANRenderer::BeginFrame()
{
	return this->m_pRendererBackend->BeginFrame();
}

bool ANRenderer::EndFrame()
{
	return this->m_pRendererBackend->EndFrame();
}

bool ANRenderer::ClearScene()
{
	return this->m_pRendererBackend->ClearScene();
}

bool ANRenderer::ResetScene(anVec2 ScreenSize)
{
	return this->m_pRendererBackend->ResetScene(ScreenSize);
}

anVec2 ANRenderer::GetScreenSize()
{
	anVec2 ScreenSize;

	this->m_pRendererBackend->GetScreenSize(this->m_CurrentWindowID, &ScreenSize);

	return ScreenSize;
}

anRect ANRenderer::InfiniteRect()
{
	return anRect(-3.402823466e+38F, -3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F);
}

bool ANRenderer::CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr)
{
	return this->m_pRendererBackend->CreateImageFromMemory(pImageSrc, iImageSize, pImageIDPtr);
}

bool ANRenderer::CreateImageFromResource(ANUniqueResource* pResource, ANImageID* pImageIDPtr)
{
	if (!pResource->ResourceIsDone())
	{
		this->SetError(__FUNCTION__ " -> Bad resource");
		return false;
	}
		
	return this->m_pRendererBackend->CreateImageFromMemory(pResource->GetResourceLocation(), pResource->GetResourceSize(), pImageIDPtr);
}

bool ANRenderer::GetImageSize(ANImageID ImageID, anVec2* pSize)
{
	return this->m_pRendererBackend->GetImageSize(ImageID, pSize);
}

void ANRenderer::FreeImage(ANImageID ImageID)
{
	this->m_pRendererBackend->FreeImage(ImageID);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anRect Pos, float Opacity)
{
	return this->m_pRendererBackend->DrawImage(this->m_CurrentWindowID, pImageID, Pos, Opacity);
}

bool ANRenderer::DrawRectangle(anRect Pos, anColor Color, float LineThickness, float Rounding)
{
	return this->m_pRendererBackend->DrawRectangle(this->m_CurrentWindowID, Pos, Color, LineThickness, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anRect Pos, anColor Color, float Rounding)
{
	return this->m_pRendererBackend->DrawFilledRectangle(this->m_CurrentWindowID, Pos, Color, Rounding);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity)
{
	return this->m_pRendererBackend->DrawImage(this->m_CurrentWindowID, pImageID, anRect(Pos, Pos + Size), Opacity);
}

bool ANRenderer::DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness)
{
	return this->m_pRendererBackend->DrawLine(this->m_CurrentWindowID, From, To, Color, LineThickness);
}

bool ANRenderer::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness, float Rounding)
{
	return this->m_pRendererBackend->DrawRectangle(this->m_CurrentWindowID, anRect(Pos, Pos + Size), Color, LineThickness, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding)
{
	return this->m_pRendererBackend->DrawFilledRectangle(this->m_CurrentWindowID, anRect(Pos, Pos + Size), Color, Rounding);
}

bool ANRenderer::DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness)
{
	return this->m_pRendererBackend->DrawTrinagle(this->m_CurrentWindowID, pt1, pt2, pt3, Color, LineThickness);
}

bool ANRenderer::DrawFilledTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color)
{
	return this->m_pRendererBackend->DrawTrinagleFilled(this->m_CurrentWindowID, pt1, pt2, pt3, Color);
}

bool ANRenderer::DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness)
{
	return this->m_pRendererBackend->DrawCircle(this->m_CurrentWindowID, Pos, Color, Radius, LineThickness);
}

bool ANRenderer::DrawFilledCircle(anVec2 Pos, anColor Color, float Radius)
{
	return this->m_pRendererBackend->DrawFilledCircle(this->m_CurrentWindowID, Pos, Color, Radius);
}

bool ANRenderer::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontIDPtr)
{
	auto BackendRenderer = this->m_pRendererBackend;
	
	auto ret = BackendRenderer->CreateFontFromFile(pszPath, FontSize, pFontIDPtr);

	if (!ret)
		this->SetError(BackendRenderer->What());

	return ret;
}

void ANRenderer::FreeFont(ANFontID* pFontIDPtr)
{
	this->m_pRendererBackend->FreeFont(pFontIDPtr);
}

bool ANRenderer::TextCalcSize(const char* pszText, anVec2* pTextSize)
{
	auto RendererBackend = this->m_pRendererBackend;

	auto ret = RendererBackend->TextCalcSize(pszText, GetFont(), pTextSize);

	if (!ret)
		this->SetError(RendererBackend->What());

	return ret;
}

bool ANRenderer::TextDraw(const char* pszText, anVec2 Pos, anColor Color)
{
	auto BackendRenderer = this->m_pRendererBackend;

	auto ret = BackendRenderer->TextDraw(this->m_CurrentWindowID, pszText, Pos, Color, GetFont(), this->m_FontAppierence);

	if (!ret)
		this->SetError(BackendRenderer->What());

	return ret;
}

bool ANRenderer::CreateGuiWindow(ANInternalGuiWindowID* pGuiWindow, anVec2 Size)
{
	auto RendererBackend = this->m_pRendererBackend;

	auto ret = RendererBackend->CreateGuiWindow(pGuiWindow, Size);

	if (!ret)
		this->SetError(RendererBackend->What());

	return ret;
}

bool ANRenderer::DeleteGuiWindow(ANInternalGuiWindowID* pGuiWindow)
{
	return this->m_pRendererBackend->DeleteGuiWindow(pGuiWindow);
}

bool ANRenderer::BeginGuiWindow(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anVec2 Size)
{
	if (!GuiWindow)
		return false;

	if (!this->m_pRendererBackend->BeginGuiWindow(GuiWindow))
		return false;

	this->m_CurrentWindowID = GuiWindow;
	this->m_CurrentWindowIDPos = Pos;
	this->m_CurrentWindowIDSize = Size;
	this->m_CurrentWindowIDRect = anRect(Pos, Pos + Size);

	this->m_pCore->GetInput()->SetCorrectWindowStartPos(this->m_CurrentWindowIDPos);

	return true;
}

bool ANRenderer::EndGuiWindow()
{
	auto ret = true;

	if (!this->m_pRendererBackend->EndGuiWindow(this->m_CurrentWindowID))
		ret = false;

	this->m_CurrentWindowID = 0;
	this->m_CurrentWindowIDPos.Clear();

	this->m_pCore->GetInput()->SetCorrectWindowStartPos(this->m_CurrentWindowIDPos);

	return ret;
}

bool ANRenderer::GetGuiWindowSize(ANInternalGuiWindowID GuiWindow, anVec2* pSize)
{
	return this->m_pRendererBackend->GetGuiWindowSize(GuiWindow, pSize);
}

bool ANRenderer::SetGuiWindowSize(ANInternalGuiWindowID* pGuiWindow, anVec2 Size)
{
	return this->m_pRendererBackend->ResizeGuiWindow(pGuiWindow, Size);
}

bool ANRenderer::DrawGuiWindow()
{
	return this->m_pRendererBackend->DrawGuiWindow(this->m_CurrentWindowID, this->m_CurrentWindowIDPos);
}

void ANRenderer::PushFont(ANFontID Font)
{
	this->m_FontID = Font;
}

void ANRenderer::PopFont()
{
	this->m_FontID = 0;
}

ANFontID ANRenderer::GetFont()
{
	return this->m_FontID != 0 ? this->m_FontID : this->m_FontIDDefault;
}

void ANRenderer::PushFontAppierence(FontAppierence Appierence)
{
	this->m_FontAppierence = Appierence;
}

void ANRenderer::PopFontAppierence()
{
	this->m_FontAppierence = FontAppierence::FONT_NONE;
}
