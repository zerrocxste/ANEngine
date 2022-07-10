#pragma once

#define ARRSIZE(v) (sizeof(v) / sizeof(*v))

typedef void* ANImageID;
typedef void* ANFontID;
typedef void* ANInternalGuiWindowID;
typedef void* ANGuiWindowID;
typedef __int64 ANPerfomanceTick;
typedef void** ANAnimationComposition;

enum FontAppierence
{
	FONT_NONE = 0,
	FONT_SHADOW = 1 << 0,
};

using fRenderInitialize = bool(__stdcall*)(HINSTANCE hInstance, HWND hWnd, void* pReversed);
using fGetRendererFunctionTable = void*(__stdcall*)();

struct ANComponents
{
	ANWindow* m_pANWindow;
	ANInput* m_pANInput;
	ANRenderer* m_ANRenderer;
	ANGame* m_pANGame;
	ANResourceManager* m_pANResourceManager;
	ANApi* m_ANApi;
	ANGui* m_ANGui;
	ANPerfomance* m_ANPerfomance;
};

struct ANRendererFuncionsTable
{
	bool(__stdcall* BeginFrame)(HWND hWnd);
	bool(__stdcall* EndFrame)(HWND hWnd);
	bool(__stdcall* ClearScene)(HWND hWnd);
	bool(__stdcall* ResetScene)(HWND hWnd, anVec2 ScreenSize);
	bool(__stdcall* GetScreenSize)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2* pAnvec2Out);
	bool(__stdcall* CreateImageFromMemory)(HWND hWnd, void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	bool(__stdcall* GetImageSize)(ANImageID ImageID, anVec2* pSize);
	void(__stdcall* FreeImage)(ANImageID* pImageIDPtr);
	bool(__stdcall* DrawImage)(HWND hWnd, ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity);
	bool(__stdcall* DrawLine)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness);
	bool(__stdcall* DrawRectangle)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding);
	bool(__stdcall* DrawFilledRectangle)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding);
	bool(__stdcall* DrawTrinagle)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness);
	bool(__stdcall* DrawTrinagleFilled)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color);
	bool(__stdcall* DrawCircle)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness);
	bool(__stdcall* DrawFilledCircle)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius);
	bool(__stdcall* CreateFontFromFile)(const char* pszPath, float FontSize, ANFontID* pFontIDPtr);
	void(__stdcall* FreeFont)(ANFontID* pFontIDPtr);
	bool(__stdcall* TextCalcSize)(HWND hWnd, const char* pszText, ANFontID FontID, anVec2* pTextSize);
	bool(__stdcall* TextDraw)(HWND hWnd, ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID, FontAppierence Appierence);
	bool(__stdcall* CreateGuiWindow)(HWND hWnd, ANInternalGuiWindowID* pGuiWindow, anVec2 Size);
	bool(__stdcall* DeleteGuiWindow)(ANInternalGuiWindowID* pGuiWindow);
	bool(__stdcall* BeginGuiWindow)(ANInternalGuiWindowID GuiWindow);
	bool(__stdcall* EndGuiWindow)(ANInternalGuiWindowID GuiWindow);
	bool(__stdcall* GetGuiWindowSize)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2* pWindowSize);
	bool(__stdcall* ResizeGuiWindow)(HWND hWnd, ANInternalGuiWindowID* GuiWindow, anVec2 WindowSize);
	bool(__stdcall* DrawGuiWindow)(HWND hWnd, ANInternalGuiWindowID GuiWindow, anVec2 Pos);
};