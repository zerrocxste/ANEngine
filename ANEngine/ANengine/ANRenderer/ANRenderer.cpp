#include "../ANEngine.h"

ANRenderer::ANRenderer(ANCore* pCore, RenderTypes RenderType) :
	IANError(),
	m_pCore(pCore),
	m_pANRendererFuncionsTable(nullptr),
	m_RenderType(RenderType),
	m_hWnd(0),
	m_RenderModule(0),
	m_CurrentWindowID(0), 
	m_CurrentWindowIDPos(anVec2()),
	m_CurrentWindowIDSize(anVec2()),
	m_FontIDDefault(0),
	m_FontID(0)
{
	
}

ANRenderer::~ANRenderer()
{

}

bool ANRenderer::Initalize()
{
	this->m_hWnd = this->m_pCore->GetWindow()->GetHWND();

	if (!LoadRendererModule())
		return false;

	if (!InvokeInitRender())
		return false;

	if (!InvokeInitFunctionTable())
		return false;

	if (!CreateDefaultFont())
		return false;

	return true;
}

bool ANRenderer::LoadRendererModule()
{
	switch (m_RenderType)
	{
	case D2D:
		this->m_RenderModule = LoadLibrary("ANEngineD2D.dll");
		break;
	case D3D9:
		this->m_RenderModule = LoadLibrary("ANEngineD3D9.dll");
		break;
	case OPENGL:
		this->m_RenderModule = LoadLibrary("ANEngineOpenGL.dll");
		break;
	}

	if (!this->m_RenderModule)
	{
		this->SetError("%s() -> Failed load %s module", __FUNCTION__, RenderTypeToStr(this->m_RenderType));
		return false;
	}

	return true;
}

bool ANRenderer::InvokeInitRender()
{
	auto pfInitializeRenderer = (fRenderInitialize)GetProcAddress(this->m_RenderModule, "InitializeRenderer");

	if (!pfInitializeRenderer)
	{
		this->SetError("%s() -> 'InitializeRenderer' function not found", __FUNCTION__);
		return false;
	}

	auto RenderInitStatus = pfInitializeRenderer(GetModuleHandle(nullptr), this->m_hWnd, nullptr);

	if (!RenderInitStatus)
	{
		this->SetError("%s() -> Initialize render failure", __FUNCTION__);
		return false;
	}

	return RenderInitStatus;
}

bool ANRenderer::InvokeInitFunctionTable()
{
	auto pfGetRendererFunctionTable = (fGetRendererFunctionTable)GetProcAddress(this->m_RenderModule, "GetRendererFunctionsTable");

	if (!pfGetRendererFunctionTable)
	{
		this->SetError("%s() -> 'GetRendererFunctionsTable' not found", __FUNCTION__);
		return false;
	}

	this->m_pANRendererFuncionsTable = (ANRendererFuncionsTable*)pfGetRendererFunctionTable();

	if (!this->m_pANRendererFuncionsTable)
	{
		this->SetError("%s() -> Render function table is invalid\n", __FUNCTION__);
		return false;
	}

	this->m_pANRendererFuncionsTable->ResetScene(this->m_hWnd, this->m_pCore->GetWindow()->GetWindow()->m_vWindowSize);

	return true;
}

bool ANRenderer::CreateDefaultFont()
{
	const char* pszDefaultFont = "C:\\Windows\\Fonts\\Arial.ttf";

	if (!this->m_pCore->GetRenderer()->CreateFontFromFile(pszDefaultFont, 20.f, &this->m_FontIDDefault))
	{
		this->SetError("%s() -> Error load default font '%s'", __FUNCTION__, pszDefaultFont);
		return false;
	}

	return true;
}

const char* ANRenderer::RenderTypeToStr(RenderTypes RenderType)
{
	switch (m_RenderType)
	{
	case D2D:
		return "Direct2D";
	case D3D9:
		return "Direct3D9";
	case OPENGL:
		return "OpenGL";
	}

	return nullptr;
}

bool ANRenderer::CheckObjectIsGuiWindowScoped(anVec2 Pos)
{
	return this->m_CurrentWindowIDRect.IsIntersected(Pos);
}

bool ANRenderer::BeginFrame()
{
	return this->m_pANRendererFuncionsTable->BeginFrame(this->m_hWnd);
}

bool ANRenderer::EndFrame()
{
	return this->m_pANRendererFuncionsTable->EndFrame(this->m_hWnd);
}

bool ANRenderer::ClearScene()
{
	return this->m_pANRendererFuncionsTable->ClearScene(this->m_hWnd);
}

bool ANRenderer::ResetScene(anVec2 ScreenSize)
{
	if (!this->m_pANRendererFuncionsTable)
		return false;

	return this->m_pANRendererFuncionsTable->ResetScene(this->m_hWnd, ScreenSize);
}

anVec2 ANRenderer::GetScreenSize()
{
	anVec2 ScreenSize;

	this->m_pANRendererFuncionsTable->GetScreenSize(this->m_hWnd, this->m_CurrentWindowID, &ScreenSize);

	return ScreenSize;
}

anRect ANRenderer::InfiniteRect()
{
	return anRect(-3.402823466e+38F, -3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F);
}

bool ANRenderer::CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr)
{
	return this->m_pANRendererFuncionsTable->CreateImageFromMemory(this->m_hWnd, pImageSrc, iImageSize, pImageIDPtr);
}

bool ANRenderer::CreateImageFromResource(ANUniqueResource* pResource, ANImageID* pImageIDPtr)
{
	if (!pResource->ResourceIsDone())
	{
		this->SetError("%s() -> Bad resource", __FUNCTION__);
		return false;
	}
		
	return this->m_pANRendererFuncionsTable->CreateImageFromMemory(this->m_hWnd, pResource->GetResourceLocation(), pResource->GetResourceSize(), pImageIDPtr);
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
	return this->m_pANRendererFuncionsTable->DrawImage(this->m_hWnd, this->m_CurrentWindowID, pImageID, Pos, Opacity);
}

bool ANRenderer::DrawRectangle(anRect Pos, anColor Color, float LineThickness, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(this->m_hWnd, this->m_CurrentWindowID, Pos, Color, LineThickness, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anRect Pos, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(this->m_hWnd, this->m_CurrentWindowID, Pos, Color, Rounding);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity)
{
	return this->m_pANRendererFuncionsTable->DrawImage(this->m_hWnd, this->m_CurrentWindowID, pImageID, anRect(Pos, Pos + Size), Opacity);
}

bool ANRenderer::DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness)
{
	return this->m_pANRendererFuncionsTable->DrawLine(this->m_hWnd, this->m_CurrentWindowID, From, To, Color, LineThickness);
}

bool ANRenderer::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(this->m_hWnd, this->m_CurrentWindowID, anRect(Pos, Pos + Size), Color, LineThickness, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(this->m_hWnd, this->m_CurrentWindowID, anRect(Pos, Pos + Size), Color, Rounding);
}

bool ANRenderer::DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness)
{
	return this->m_pANRendererFuncionsTable->DrawTrinagle(this->m_hWnd, this->m_CurrentWindowID, pt1, pt2, pt3, Color, LineThickness);
}

bool ANRenderer::DrawFilledTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color)
{
	return this->m_pANRendererFuncionsTable->DrawTrinagleFilled(this->m_hWnd, this->m_CurrentWindowID, pt1, pt2, pt3, Color);
}

bool ANRenderer::DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness)
{
	return this->m_pANRendererFuncionsTable->DrawCircle(this->m_hWnd, this->m_CurrentWindowID, Pos, Color, Radius, LineThickness);
}

bool ANRenderer::DrawFilledCircle(anVec2 Pos, anColor Color, float Radius)
{
	return this->m_pANRendererFuncionsTable->DrawFilledCircle(this->m_hWnd, this->m_CurrentWindowID, Pos, Color, Radius);
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
	return this->m_pANRendererFuncionsTable->TextCalcSize(this->m_hWnd, pszText, GetFont(), pTextSize);
}

bool ANRenderer::TextDraw(const char* pszText, anVec2 Pos, anColor Color)
{
	return this->m_pANRendererFuncionsTable->TextDraw(this->m_hWnd, this->m_CurrentWindowID, pszText, Pos, Color, GetFont());
}

bool ANRenderer::CreateGuiWindow(ANInternalGuiWindowID* pGuiWindow, anVec2 Size)
{
	return this->m_pANRendererFuncionsTable->CreateGuiWindow(this->m_hWnd, pGuiWindow, Size);
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
	return this->m_pANRendererFuncionsTable->GetGuiWindowSize(this->m_hWnd, GuiWindow, pSize);
}

bool ANRenderer::SetGuiWindowSize(ANInternalGuiWindowID* pGuiWindow, anVec2 Size)
{
	return this->m_pANRendererFuncionsTable->ResizeGuiWindow(this->m_hWnd, pGuiWindow, Size);
}

bool ANRenderer::DrawGuiWindow()
{
	return this->m_pANRendererFuncionsTable->DrawGuiWindow(this->m_hWnd, this->m_CurrentWindowID, this->m_CurrentWindowIDPos);
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