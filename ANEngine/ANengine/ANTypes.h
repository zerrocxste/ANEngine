#pragma once

#define ARRSIZE(v) (sizeof(v) / sizeof(*v))

typedef void* ANModuleHandle;
typedef void* ANWindowHandle;

struct ANWindowData
{
	char m_WindowTitle[256];
	bool m_bHasWindowFrame;
	anVec2 m_vWindowPosition;
	anVec2 m_vWindowSize;
};

typedef void* ANImageID;
typedef void* ANFontID;
typedef void* ANInternalGuiWindowID;
typedef void* ANGuiWindowID;
typedef __int64 ANPerfomanceTick;
typedef void** ANAnimationComposition;

enum RGBA;

enum CursorKey;
struct KeyInformation;

enum FontAppierence;

struct ANWorldMetrics;
struct ANUniqueInteractionMesssage;

struct ANComponents
{
	ANInput* m_pANInput;
	ANRenderer* m_ANRenderer;
	ANGame* m_pANGame;
	ANResourceManager* m_pANResourceManager;
	ANApi* m_ANApi;
	ANGui* m_ANGui;
	ANPerfomance* m_ANPerfomance;
	ANPlatform* m_pANPlatform;
};

struct ANRendererFuncionsTable
{
	bool(* BeginFrame)(ANWindowHandle Window);
	bool(* EndFrame)(ANWindowHandle Window);
	bool(* ClearScene)(ANWindowHandle Window);
	bool(* ResetScene)(ANWindowHandle Window, anVec2 ScreenSize);
	bool(* GetScreenSize)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2* pAnvec2Out);
	bool(* CreateImageFromMemory)(ANWindowHandle Window, void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	bool(* GetImageSize)(ANImageID ImageID, anVec2* pSize);
	void(* FreeImage)(ANImageID* pImageIDPtr);
	bool(* DrawImage)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity);
	bool(* DrawLine)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness);
	bool(* DrawRectangle)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding);
	bool(* DrawFilledRectangle)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding);
	bool(* DrawTrinagle)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness);
	bool(* DrawTrinagleFilled)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color);
	bool(* DrawCircle)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness);
	bool(* DrawFilledCircle)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius);
	bool(* CreateFontFromFile)(const char* pszPath, float FontSize, ANFontID* pFontIDPtr);
	void(* FreeFont)(ANFontID* pFontIDPtr);
	bool(* TextCalcSize)(ANWindowHandle Window, const char* pszText, ANFontID FontID, anVec2* pTextSize);
	bool(* TextDraw)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID, FontAppierence Appierence);
	bool(* CreateGuiWindow)(ANWindowHandle Window, ANInternalGuiWindowID* pGuiWindow, anVec2 Size);
	bool(* DeleteGuiWindow)(ANInternalGuiWindowID* pGuiWindow);
	bool(* BeginGuiWindow)(ANInternalGuiWindowID GuiWindow);
	bool(* EndGuiWindow)(ANInternalGuiWindowID GuiWindow);
	bool(* GetGuiWindowSize)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2* pWindowSize);
	bool(* ResizeGuiWindow)(ANWindowHandle Window, ANInternalGuiWindowID* GuiWindow, anVec2 WindowSize);
	bool(* DrawGuiWindow)(ANWindowHandle Window, ANInternalGuiWindowID GuiWindow, anVec2 Pos);
};