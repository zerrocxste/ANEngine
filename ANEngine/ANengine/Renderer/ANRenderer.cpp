#include "../ANEngine.h"

ANRenderer::ANRenderer(RenderTypes RenderType) :
	IANError(),
	m_RenderType(RenderType),
	m_RenderModule(0),
	m_hWnd(0)
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
	auto pInitializeRenderer = (fRenderInitialize)GetProcAddress(this->m_RenderModule, "InitializeRenderer");

	if (!pInitializeRenderer)
	{
		this->SetError("%s() -> 'InitializeRenderer' function not found", __FUNCTION__);
		return false;
	}

	auto RenderInitStatus = pInitializeRenderer(GetModuleHandle(nullptr), this->m_hWnd);

	if (!RenderInitStatus)
	{
		this->SetError("%s() -> Initialize render failure", __FUNCTION__);
		return false;
	}

	return RenderInitStatus;
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
