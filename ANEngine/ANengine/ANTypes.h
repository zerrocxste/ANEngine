#pragma once

typedef void* ANImageID;
typedef void* ANFontID;

using fRenderInitialize = bool(__stdcall*)(HINSTANCE hInstance, HWND hWnd, void* pInformationOut);
using fGetRendererFunctionTable = void*(__stdcall*)();

enum RenderTypes
{
	D2D,
	D3D9,
	OPENGL
};

enum RGBA
{
	RED,
	GREEN,
	BLUE,
	ALPHA,
	RGBA_MAX_SIZE
};

struct ANRendererFuncionsTable
{
	bool(__stdcall* BeginFrame)();
	bool(__stdcall* EndFrame)();
	bool(__stdcall* ResetScene)(WPARAM wParam, LPARAM lParam);
	bool(__stdcall* GetScreenSize)(anVec2* pAnvec2Out);
	bool(__stdcall* CreateImageFromMemory)(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	bool(__stdcall* DrawImage)(ANImageID pImageID, anRect Pos, float Opacity);
	bool(__stdcall* DrawRectangle)(anRect Pos, anColor Color, float Rounding);
	bool(__stdcall* DrawFilledRectangle)(anRect Pos, anColor Color, float Rounding);
	bool(__stdcall* DrawCircle)(anVec2 Pos, anColor Color, float Radius);
	bool(__stdcall* DrawFilledCircle)(anVec2 Pos, anColor Color, float Radius);
	bool(__stdcall* CreateFontFromFile)(const char* pszPath, float FontSize, ANFontID* pFontID);
	bool(__stdcall* TextDraw)(const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont);
};