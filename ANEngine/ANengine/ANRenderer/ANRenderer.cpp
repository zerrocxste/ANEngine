#include "../ANEngine.h"

ANRenderer::ANRenderer(ANCore* pCore, bool bVerticalSync) :
	IANError(),
	m_pCore(pCore),
	m_bEnableVerticalSync(bVerticalSync),
	m_pANRendererFuncionsTable(nullptr),
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
	if (!renderBackend::InitializeRenderer(this->m_Window, nullptr))
	{
		this->SetError(__FUNCTION__ " > Error initialize render");
		return false;
	}

	this->m_pANRendererFuncionsTable = renderBackend::GetRendererFunctionsTable();

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
	return this->m_pANRendererFuncionsTable->BeginFrame(this->m_Window);
}

bool ANRenderer::EndFrame()
{
	return this->m_pANRendererFuncionsTable->EndFrame(this->m_Window);
}

bool ANRenderer::ClearScene()
{
	return this->m_pANRendererFuncionsTable->ClearScene(this->m_Window);
}

bool ANRenderer::ResetScene(anVec2 ScreenSize)
{
	if (!this->m_pANRendererFuncionsTable)
		return false;

	return this->m_pANRendererFuncionsTable->ResetScene(this->m_Window, ScreenSize);
}

anVec2 ANRenderer::GetScreenSize()
{
	anVec2 ScreenSize;

	this->m_pANRendererFuncionsTable->GetScreenSize(this->m_Window, this->m_CurrentWindowID, &ScreenSize);

	return ScreenSize;
}

anRect ANRenderer::InfiniteRect()
{
	return anRect(-3.402823466e+38F, -3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F);
}

bool ANRenderer::CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr)
{
	return this->m_pANRendererFuncionsTable->CreateImageFromMemory(this->m_Window, pImageSrc, iImageSize, pImageIDPtr);
}

bool ANRenderer::CreateImageFromResource(ANUniqueResource* pResource, ANImageID* pImageIDPtr)
{
	if (!pResource->ResourceIsDone())
	{
		this->SetError(__FUNCTION__ " -> Bad resource");
		return false;
	}
		
	return this->m_pANRendererFuncionsTable->CreateImageFromMemory(this->m_Window, pResource->GetResourceLocation(), pResource->GetResourceSize(), pImageIDPtr);
}

bool ANRenderer::GetImageSize(ANImageID ImageID, anVec2* pSize)
{
	return this->m_pANRendererFuncionsTable->GetImageSize(ImageID, pSize);
}

void ANRenderer::FreeImage(ANImageID* pImageIDPtr)
{
	this->m_pANRendererFuncionsTable->FreeImage(pImageIDPtr);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anRect Pos, float Opacity)
{
	return this->m_pANRendererFuncionsTable->DrawImage(this->m_Window, this->m_CurrentWindowID, pImageID, Pos, Opacity);
}

bool ANRenderer::DrawRectangle(anRect Pos, anColor Color, float LineThickness, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(this->m_Window, this->m_CurrentWindowID, Pos, Color, LineThickness, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anRect Pos, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(this->m_Window, this->m_CurrentWindowID, Pos, Color, Rounding);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity)
{
	return this->m_pANRendererFuncionsTable->DrawImage(this->m_Window, this->m_CurrentWindowID, pImageID, anRect(Pos, Pos + Size), Opacity);
}

bool ANRenderer::DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness)
{
	return this->m_pANRendererFuncionsTable->DrawLine(this->m_Window, this->m_CurrentWindowID, From, To, Color, LineThickness);
}

bool ANRenderer::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(this->m_Window, this->m_CurrentWindowID, anRect(Pos, Pos + Size), Color, LineThickness, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(this->m_Window, this->m_CurrentWindowID, anRect(Pos, Pos + Size), Color, Rounding);
}

bool ANRenderer::DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness)
{
	return this->m_pANRendererFuncionsTable->DrawTrinagle(this->m_Window, this->m_CurrentWindowID, pt1, pt2, pt3, Color, LineThickness);
}

bool ANRenderer::DrawFilledTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color)
{
	return this->m_pANRendererFuncionsTable->DrawTrinagleFilled(this->m_Window, this->m_CurrentWindowID, pt1, pt2, pt3, Color);
}

bool ANRenderer::DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness)
{
	return this->m_pANRendererFuncionsTable->DrawCircle(this->m_Window, this->m_CurrentWindowID, Pos, Color, Radius, LineThickness);
}

bool ANRenderer::DrawFilledCircle(anVec2 Pos, anColor Color, float Radius)
{
	return this->m_pANRendererFuncionsTable->DrawFilledCircle(this->m_Window, this->m_CurrentWindowID, Pos, Color, Radius);
}

bool ANRenderer::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontIDPtr)
{
	return this->m_pANRendererFuncionsTable->CreateFontFromFile(pszPath, FontSize, pFontIDPtr);
}

void ANRenderer::FreeFont(ANFontID* pFontIDPtr)
{
	this->m_pANRendererFuncionsTable->FreeFont(pFontIDPtr);
}

bool ANRenderer::TextCalcSize(const char* pszText, anVec2* pTextSize)
{
	return this->m_pANRendererFuncionsTable->TextCalcSize(this->m_Window, pszText, GetFont(), pTextSize);
}

bool ANRenderer::TextDraw(const char* pszText, anVec2 Pos, anColor Color)
{
	return this->m_pANRendererFuncionsTable->TextDraw(this->m_Window, this->m_CurrentWindowID, pszText, Pos, Color, GetFont(), this->m_FontAppierence);
}

bool ANRenderer::CreateGuiWindow(ANInternalGuiWindowID* pGuiWindow, anVec2 Size)
{
	return this->m_pANRendererFuncionsTable->CreateGuiWindow(this->m_Window, pGuiWindow, Size);
}

bool ANRenderer::DeleteGuiWindow(ANInternalGuiWindowID* pGuiWindow)
{
	return this->m_pANRendererFuncionsTable->DeleteGuiWindow(pGuiWindow);
}

bool ANRenderer::BeginGuiWindow(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anVec2 Size)
{
	if (!GuiWindow)
		return false;

	if (!this->m_pANRendererFuncionsTable->BeginGuiWindow(GuiWindow))
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

	if (!this->m_pANRendererFuncionsTable->EndGuiWindow(this->m_CurrentWindowID))
		ret = false;

	this->m_CurrentWindowID = 0;
	this->m_CurrentWindowIDPos.Clear();

	this->m_pCore->GetInput()->SetCorrectWindowStartPos(this->m_CurrentWindowIDPos);

	return ret;
}

bool ANRenderer::GetGuiWindowSize(ANInternalGuiWindowID GuiWindow, anVec2* pSize)
{
	return this->m_pANRendererFuncionsTable->GetGuiWindowSize(this->m_Window, GuiWindow, pSize);
}

bool ANRenderer::SetGuiWindowSize(ANInternalGuiWindowID* pGuiWindow, anVec2 Size)
{
	return this->m_pANRendererFuncionsTable->ResizeGuiWindow(this->m_Window, pGuiWindow, Size);
}

bool ANRenderer::DrawGuiWindow()
{
	return this->m_pANRendererFuncionsTable->DrawGuiWindow(this->m_Window, this->m_CurrentWindowID, this->m_CurrentWindowIDPos);
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
