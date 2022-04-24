#pragma once

#define ARRSIZE(v) (sizeof(v) / sizeof(*v))

typedef void* ANImageID;
typedef void* ANFontID;

using fRenderInitialize = bool(__stdcall*)(HINSTANCE hInstance, HWND hWnd, void* pReversed);
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

enum CursorKey
{
	MAIN_FIRST,
	MAIN_SECOND,
	SECONDARY,
	ADDITIONAL_1,
	ADDITIONAL_2
};

struct KeyInformation
{
	bool m_bIsDowned;
	bool m_bIsReleased;
	float m_flDownTime;
};

struct ANComponents
{
	ANWindow* m_pANWindow;
	ANInput* m_pANInput;
	ANRenderer* m_ANRenderer;
	ANGame* m_pANGame;
	ANResourceManager* m_pANResourceManager;
	ANScene* m_pANScene;
	ANApi* m_ANApi;
	ANGui* m_ANGui;
};

struct ANRendererFuncionsTable
{
	bool(__stdcall* BeginFrame)(HWND hWnd);
	bool(__stdcall* EndFrame)(HWND hWnd);
	bool(__stdcall* ClearScene)(HWND hWnd);
	bool(__stdcall* ResetScene)(HWND hWnd, anVec2 ScreenSize);
	bool(__stdcall* GetScreenSize)(HWND hWnd, anVec2* pAnvec2Out);
	bool(__stdcall* CreateImageFromMemory)(HWND hWnd, void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	void(__stdcall* FreeImage)(ANImageID* pImageIDPtr);
	bool(__stdcall* DrawImage)(HWND hWnd, ANImageID pImageID, anRect Pos, float Opacity);
	bool(__stdcall* DrawLine)(HWND hWnd, anVec2 From, anVec2 To, anColor Color, float LineThickness);
	bool(__stdcall* DrawRectangle)(HWND hWnd, anRect Pos, anColor Color, float LineThickness, float Rounding);
	bool(__stdcall* DrawFilledRectangle)(HWND hWnd, anRect Pos, anColor Color, float Rounding);
	bool(__stdcall* DrawTrinagle)(HWND hWnd, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness);
	bool(__stdcall* DrawTrinagleFilled)(HWND hWnd, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color);
	bool(__stdcall* DrawCircle)(HWND hWnd, anVec2 Pos, anColor Color, float Radius, float LineThickness);
	bool(__stdcall* DrawFilledCircle)(HWND hWnd, anVec2 Pos, anColor Color, float Radius);
	bool(__stdcall* CreateFontFromFile)(const char* pszPath, float FontSize, ANFontID* pFontIDPtr);
	void(__stdcall* FreeFont)(ANFontID* pFontIDPtr);
	bool(__stdcall* TextDraw)(HWND hWnd, const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont);
};