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

	bool BeginFrame() override;
	bool EndFrame() override;
	bool ClearScene() override;
	bool ResetScene(anVec2 ScreenSize) override;
	bool GetScreenSize(ANInternalGuiWindowID GuiWindow, anVec2* pAnvec2Out) override;
	bool CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr) override;
	bool GetImageSize(ANImageID ImageID, anVec2* pSize) override;
	void FreeImage(ANImageID ImageID) override;
	bool DrawImage(ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity) override;
	bool DrawLine(ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness);
	bool DrawRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding) override;
	bool DrawFilledRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding) override;
	bool DrawCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness) override;
	bool DrawTrinagle(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness) override;
	bool DrawTrinagleFilled(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color) override;
	bool DrawFilledCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius) override;
	bool CreateDefaultFont(ANFontID* pFontID) override;
	bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontIDPtr) override;
	void FreeFont(ANFontID* pFontIDPtr) override;
	bool TextCalcSize(const char* pszText, ANFontID FontID, anVec2* pTextSize) override;
	bool TextDraw(ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID, FontAppierence Appierence) override;
	bool CreateGuiWindow(ANInternalGuiWindowID* pGuiWindow, anVec2 Size) override;
	bool DeleteGuiWindow(ANInternalGuiWindowID* GuiWindow) override;
	bool BeginGuiWindow(ANInternalGuiWindowID GuiWindow) override;
	bool EndGuiWindow(ANInternalGuiWindowID GuiWindow) override;
	bool GetGuiWindowSize(ANInternalGuiWindowID GuiWindow, anVec2* pWindowSize) override;
	bool ResizeGuiWindow(ANInternalGuiWindowID* GuiWindow, anVec2 WindowSize) override;
	bool DrawGuiWindow(ANInternalGuiWindowID GuiWindow, anVec2 Pos) override;
};
#endif // BACKEND_DIRECT2D