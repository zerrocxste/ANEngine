#pragma once

class ANRenderer : public IANError
{
public:
	ANRenderer(ANCore* pCore, RenderTypes RenderType);
	~ANRenderer();

	bool Initalize();

	bool PrepareScene();

	bool BeginFrame();
	bool EndFrame();

	bool ClearScene();
	bool ResetScene(anVec2 ScreenSize);

	anVec2 GetScreenSize();
	anRect InfiniteRect();

	int GetFramePerSecond();
	double GetFrameTime();

	void SetMaxFps(int iMaxFps);

	bool CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	bool CreateImageFromResource(ANUniqueResource* pResource, ANImageID* pImageIDPtr);
	void FreeImage(ANImageID* pImageIDPtr);
	bool DrawImage(ANImageID pImageID, anRect Pos, float Opacity = 1.f);
	bool DrawRectangle(anRect Pos, anColor Color, float LineThickness = 1.f, float Rounding = 0.f);
	bool DrawFilledRectangle(anRect Pos, anColor Color, float Rounding = 0.f);
	bool DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity = 1.f);
	bool DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness = 1.f);
	bool DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness = 1.f, float Rounding = 0.f);
	bool DrawFilledRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding = 0.f);
	bool DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness);
	bool DrawFilledTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color);
	bool DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness = 1.f);
	bool DrawFilledCircle(anVec2 Pos, anColor Color, float Radius);
	bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontIDPtr);
	void FreeFont(ANFontID* pFontIDPtr);
	bool TextCalcSize(const char* pszText, anVec2* pTextSize);
	bool TextDraw(const char* pszText, anVec2 Pos, anColor Color);
	bool CreateGuiWindow(ANInternalGuiWindowID* pGuiWindow, anVec2 Size);
	bool DeleteGuiWindow(ANInternalGuiWindowID* pGuiWindow);
	bool BeginGuiWindow(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anVec2 Size);
	bool EndGuiWindow();
	bool GetGuiWindowSize(ANInternalGuiWindowID GuiWindow, anVec2* pSize);
	bool SetGuiWindowSize(ANInternalGuiWindowID* pGuiWindow, anVec2 Size);
	bool DrawGuiWindow();

	void PushFont(ANFontID Font);
	void PopFont();
	ANFontID GetFont();
private:
	ANCore* m_pCore;

	ANRendererFuncionsTable* m_pANRendererFuncionsTable;

	RenderTypes m_RenderType;
	HWND m_hWnd;
	HMODULE m_RenderModule;

	__int64 m_FpsSecondTimer;
	int m_iCurrentFpsCounter;
	int m_iFpsCounter;
	__int64 m_BeginFrameTick;
	__int64 m_EndFrameTick;
	double m_MaxFpsFrameTime;

	bool m_bFrameTimeIsGrabbed;
	int m_iCurrentSkipperFrame;

	int m_iMaxFps;

	ANInternalGuiWindowID m_CurrentWindowID;
	anVec2 m_CurrentWindowIDPos;
	anVec2 m_CurrentWindowIDSize;

	ANFontID m_AutoLoadedDefaultFont;
	ANFontID m_FontID;

	bool LoadRendererModule();
	bool InvokeInitRender();
	bool InvokeInitFunctionTable();
	bool CreateDefaultFont();

	__int64 GetTick();

	const char* RenderTypeToStr(RenderTypes RenderType);
};
