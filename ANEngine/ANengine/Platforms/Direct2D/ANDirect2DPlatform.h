#pragma once

#ifdef BACKEND_DIRECT2D
#include <d2d1.h>
#pragma comment (lib, "d2d1.lib")

#include <dwrite.h>
#pragma comment (lib, "dwrite.lib")

#include <wincodec.h>
#pragma comment (lib, "windowscodecs.lib")

typedef void* TextCacheID;

struct DWriteTextCache
{
	const char* m_szText;
	wchar_t* m_wszText;
	int m_iTextLength;
	int m_iTotalSumOfSymStr;
	IDWriteTextFormat* m_pDWriteTextFormat;
	IDWriteTextLayout* m_pDWriteTextLayout;
	DWRITE_TEXT_METRICS m_dwrTextMetrics;
};

class ANRendererlatformD2D : public IANRendererBackend
{
private:
	struct singleton_
	{
		static int iWorkingLinkCount;

		bool bCriticalSectionInitialized;
		CRITICAL_SECTION csInitializeRenderer;

		ID2D1Factory* pFactory;
		IWICImagingFactory* pWICFactory;
		IDWriteFactory* pDWriteFactory;
	
		std::map<TextCacheID, DWriteTextCache> mDWriteTextCache;

		bool CreateD2D1Factory();
		bool CreateWICFactory();
		bool CreateDirectWriteFactory();

		void Initialize();

		__forceinline bool ProcessTextCache(const char* pszText, ANFontID FontID, DWriteTextCache* pCachedTextElement);
	} 
	static m_singleton;

	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pColorBrushBlack;
	ID2D1SolidColorBrush* m_pColorBrush;
	bool m_bEnabledVerticalSync;

	bool Initialize(HWND hWnd, bool bVerticalSyncEnabled);
	bool CreateRenderTarget(ANWindowHandle WindowHandle, bool bVerticalSyncEnabled);
	bool CreateGlobalBrush();
public:
	virtual bool InitializeRenderer(ANWindowHandle WindowHandle, bool bEnableVerticalSync, void* pReversed);

	virtual bool BeginFrame();
	virtual bool EndFrame();
	virtual bool ClearScene();
	virtual bool ResetScene(anVec2 ScreenSize);
	virtual bool GetScreenSize(ANInternalGuiWindowID GuiWindow, anVec2* pAnvec2Out);
	virtual bool CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	virtual bool GetImageSize(ANImageID ImageID, anVec2* pSize);
	virtual void FreeImage(ANImageID ImageID);
	virtual bool DrawImage(ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity);
	virtual bool DrawLine(ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness);
	virtual bool DrawRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding);
	virtual bool DrawFilledRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding);
	virtual bool DrawCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness);
	virtual bool DrawTrinagle(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness);
	virtual bool DrawTrinagleFilled(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color);
	virtual bool DrawFilledCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius);
	virtual bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontIDPtr);
	virtual void FreeFont(ANFontID* pFontIDPtr);
	virtual bool TextCalcSize(const char* pszText, ANFontID FontID, anVec2* pTextSize);
	virtual bool TextDraw(ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID, FontAppierence Appierence);
	virtual bool CreateGuiWindow(ANInternalGuiWindowID* pGuiWindow, anVec2 Size);
	virtual bool DeleteGuiWindow(ANInternalGuiWindowID* GuiWindow);
	virtual bool BeginGuiWindow(ANInternalGuiWindowID GuiWindow);
	virtual bool EndGuiWindow(ANInternalGuiWindowID GuiWindow);
	virtual bool GetGuiWindowSize(ANInternalGuiWindowID GuiWindow, anVec2* pWindowSize);
	virtual bool ResizeGuiWindow(ANInternalGuiWindowID* GuiWindow, anVec2 WindowSize);
	virtual bool DrawGuiWindow(ANInternalGuiWindowID GuiWindow, anVec2 Pos);
};
#endif // BACKEND_DIRECT2D