#include "../ANEngine.h"

D2DOutInformation* g_pD2DOutInformation;

ANRenderer::ANRenderer(ANCore* pCore, RenderTypes RenderType) :
	IANError(),
	m_pCore(pCore),
	m_RenderType(RenderType),
	m_RenderModule(0),
	m_hWnd(0),
	m_pANRendererFuncionsTable(nullptr)
{
	
}

ANRenderer::~ANRenderer()
{

}

bool ANRenderer::Initalize(HWND hWnd)
{
	this->m_hWnd = hWnd;

	if (!LoadRendererModule())
		return false;

	if (!InvokeInitRender())
		return false;

	if (!InvokeInitFunctionTable())
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

	auto RenderInitStatus = pfInitializeRenderer(GetModuleHandle(nullptr), this->m_hWnd, &g_pD2DOutInformation);

	if (!RenderInitStatus || !g_pD2DOutInformation)
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
		this->SetError("%s() -> 'GetRendererFunctionsTable' nout found", __FUNCTION__);
		return false;
	}

	this->m_pANRendererFuncionsTable = (ANRendererFuncionsTable*)pfGetRendererFunctionTable();

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

bool ANRenderer::BeginFrame()
{
	return this->m_pANRendererFuncionsTable->BeginFrame();
}

bool ANRenderer::EndFrame()
{
	return this->m_pANRendererFuncionsTable->EndFrame();
}

bool ANRenderer::ResetScene(WPARAM wParam, LPARAM lParam)
{
	return this->m_pANRendererFuncionsTable->ResetScene(wParam, lParam);
}

anVec2 ANRenderer::GetScreenSize()
{
	anVec2 ScreenSize;

	this->m_pANRendererFuncionsTable->GetScreenSize(&ScreenSize);

	return ScreenSize;
}

anRect ANRenderer::InfiniteRect()
{
	return anRect(-3.402823466e+38F, -3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F);
}

bool ANRenderer::CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr)
{
	return this->m_pANRendererFuncionsTable->CreateImageFromMemory(pImageSrc, iImageSize, pImageIDPtr);
}

bool ANRenderer::CreateImageFromResource(ANUniqueResource* pResource, ANImageID* pImageIDPtr)
{
	if (!pResource->ResourceIsDone())
		return false;

	return this->m_pANRendererFuncionsTable->CreateImageFromMemory(pResource->GetResourceLocation(), pResource->GetResourceSize(), pImageIDPtr);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anRect Pos, float Opacity)
{
	return this->m_pANRendererFuncionsTable->DrawImage(pImageID, Pos, Opacity);
}

bool ANRenderer::DrawRectangle(anRect Pos, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(Pos, Color, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anRect Pos, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(Pos, Color, Rounding);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity)
{
	return this->m_pANRendererFuncionsTable->DrawImage(pImageID, anRect(Pos, Pos + Size), Opacity);
}

bool ANRenderer::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(anRect(Pos, Pos + Size), Color, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(anRect(Pos, Pos + Size), Color, Rounding);
}

bool ANRenderer::DrawCircle(anVec2 Pos, anColor Color, float Radius)
{
	return this->m_pANRendererFuncionsTable->DrawCircle(Pos, Color, Radius);
}

bool ANRenderer::DrawFilledCircle(anVec2 Pos, anColor Color, float Radius)
{
	return this->m_pANRendererFuncionsTable->DrawFilledCircle(Pos, Color, Radius);
}

bool ANRenderer::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID)
{
	return this->m_pANRendererFuncionsTable->CreateFontFromFile(pszPath, FontSize, pFontID);
}

bool ANRenderer::TextDraw(const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont)
{
	return this->m_pANRendererFuncionsTable->TextDraw(pszText, Pos, Color, pFont);
}