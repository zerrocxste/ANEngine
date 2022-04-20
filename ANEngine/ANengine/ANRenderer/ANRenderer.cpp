#include "../ANEngine.h"

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

bool ANRenderer::Initalize()
{
	this->m_hWnd = this->m_pCore->GetWindow()->GetHWND();

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

	return true;
}

void ANRenderer::SetMaxFps(int iMaxFps)
{
	this->m_iMaxFps = iMaxFps;
}

__int64 ANRenderer::GetTick()
{
	__int64 T = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&T);
	return T;
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

bool ANRenderer::PrepareScene()
{
	//this->m_iMaxFps = 60;

	if (this->m_iMaxFps > 0)
	{
		if (this->m_iCurrentSkipperFrame > 0)
		{
			if (!this->m_bFrameTimeIsGrabbed) 
			{
				this->m_bFrameTimeIsGrabbed = true;
				this->m_BeginFrameTick = GetTick();
			}
			this->m_iCurrentSkipperFrame--;
			return false;
		}

		this->m_iCurrentSkipperFrame = ((1000000 * 2.5f) / this->m_iMaxFps) + ((this->m_EndFrameTick - this->m_BeginFrameTick) / 10);
		this->m_bFrameTimeIsGrabbed = false;

		printf("Frame to skip: %d\n", this->m_iCurrentSkipperFrame);
	}
	else
	{
		this->m_BeginFrameTick = GetTick();
	}

	return true;
}

bool ANRenderer::BeginFrame()
{
	auto ret = this->m_pANRendererFuncionsTable->BeginFrame(this->m_hWnd);

	if (!this->m_FpsSecondTimer)
		this->m_FpsSecondTimer = this->m_BeginFrameTick;

	return ret;
}

bool ANRenderer::EndFrame()
{
	this->m_iCurrentFpsCounter++;

	this->m_EndFrameTick = GetTick();

	if ((this->m_EndFrameTick - this->m_FpsSecondTimer) / 10000 >= 1000)
	{
		this->m_iFpsCounter = this->m_iCurrentFpsCounter;
		this->m_FpsSecondTimer = 0;
		this->m_iCurrentFpsCounter = 0;
	}

	this->m_MaxFpsFrameTime = (double)(this->m_EndFrameTick - this->m_BeginFrameTick) / 10000000;

	return this->m_pANRendererFuncionsTable->EndFrame(this->m_hWnd);
}

bool ANRenderer::ClearScene()
{
	return this->m_pANRendererFuncionsTable->ClearScene(this->m_hWnd);
}

bool ANRenderer::ResetScene(WPARAM wParam, LPARAM lParam)
{
	return this->m_pANRendererFuncionsTable->ResetScene(this->m_hWnd, wParam, lParam);
}

anVec2 ANRenderer::GetScreenSize()
{
	anVec2 ScreenSize;

	this->m_pANRendererFuncionsTable->GetScreenSize(this->m_hWnd, &ScreenSize);

	return ScreenSize;
}

anRect ANRenderer::InfiniteRect()
{
	return anRect(-3.402823466e+38F, -3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F);
}

int ANRenderer::GetFramePerSecond()
{
	return this->m_iFpsCounter;
}

double ANRenderer::GetFrameTime()
{
	return this->m_MaxFpsFrameTime;
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

bool ANRenderer::DrawImage(ANImageID pImageID, anRect Pos, float Opacity)
{
	return this->m_pANRendererFuncionsTable->DrawImage(this->m_hWnd, pImageID, Pos, Opacity);
}

bool ANRenderer::DrawRectangle(anRect Pos, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(this->m_hWnd, Pos, Color, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anRect Pos, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(this->m_hWnd, Pos, Color, Rounding);
}

bool ANRenderer::DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity)
{
	return this->m_pANRendererFuncionsTable->DrawImage(this->m_hWnd, pImageID, anRect(Pos, Pos + Size), Opacity);
}

bool ANRenderer::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawRectangle(this->m_hWnd, anRect(Pos, Pos + Size), Color, Rounding);
}

bool ANRenderer::DrawFilledRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding)
{
	return this->m_pANRendererFuncionsTable->DrawFilledRectangle(this->m_hWnd, anRect(Pos, Pos + Size), Color, Rounding);
}

bool ANRenderer::DrawCircle(anVec2 Pos, anColor Color, float Radius)
{
	return this->m_pANRendererFuncionsTable->DrawCircle(this->m_hWnd, Pos, Color, Radius);
}

bool ANRenderer::DrawFilledCircle(anVec2 Pos, anColor Color, float Radius)
{
	return this->m_pANRendererFuncionsTable->DrawFilledCircle(this->m_hWnd, Pos, Color, Radius);
}

bool ANRenderer::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID)
{
	return this->m_pANRendererFuncionsTable->CreateFontFromFile(pszPath, FontSize, pFontID);
}

bool ANRenderer::TextDraw(const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont)
{
	return this->m_pANRendererFuncionsTable->TextDraw(this->m_hWnd, pszText, Pos, Color, pFont);
}