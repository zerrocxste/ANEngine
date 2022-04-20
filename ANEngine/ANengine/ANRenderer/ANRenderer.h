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
	bool ResetScene(WPARAM wParam, LPARAM lParam);

	anVec2 GetScreenSize();
	anRect InfiniteRect();

	int GetFramePerSecond();
	double GetFrameTime();

	void SetMaxFps(int iMaxFps);

	bool CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	bool CreateImageFromResource(ANUniqueResource* pResource, ANImageID* pImageIDPtr);
	bool DrawImage(ANImageID pImageID, anRect Pos, float Opacity = 1.f);
	bool DrawRectangle(anRect Pos, anColor Color, float Rounding = 0.f);
	bool DrawFilledRectangle(anRect Pos, anColor Color, float Rounding = 0.f);
	bool DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity = 1.f);
	bool DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding = 0.f);
	bool DrawFilledRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding = 0.f);
	bool DrawCircle(anVec2 Pos, anColor Color, float Radius);
	bool DrawFilledCircle(anVec2 Pos, anColor Color, float Radius);
	bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID);
	bool TextDraw(const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont);

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

	bool LoadRendererModule();
	bool InvokeInitRender();
	bool InvokeInitFunctionTable();

	__int64 GetTick();

	const char* RenderTypeToStr(RenderTypes RenderType);
};
