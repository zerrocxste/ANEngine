#pragma once

enum RenderTypes
{
	D2D,
	D3D9,
	OPENGL
};

using fRenderInitialize = bool(__stdcall*)(HINSTANCE hInstance, HWND hWnd);

class ANRenderer : public IANError
{
public:
	ANRenderer(RenderTypes RenderType);
	~ANRenderer();

	bool Initalize(HWND hWnd);
	bool LoadRendererModule();
	bool InvokeInitRender();

	const char* RenderTypeToStr(RenderTypes RenderType);
private:
	RenderTypes m_RenderType;
	HWND m_hWnd;
	HMODULE m_RenderModule;
};
