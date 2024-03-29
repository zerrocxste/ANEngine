#pragma once

enum FontAppierence
{
	FONT_NONE = 0,
	FONT_SHADOW = 1 << 0,
};

class ANRenderer : public IANError
{
	friend ANPlatform;
public:
	ANRenderer(ANCore* pCore, bool bVerticalSync);
	~ANRenderer();

	bool Initalize();

	bool BeginFrame();
	bool EndFrame();

	bool ClearScene();
	bool ResetScene(anVec2 ScreenSize);

	anVec2 GetScreenSize();
	anRect InfiniteRect();

	bool CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr);
	bool CreateImageFromResource(ANUniqueResource* pResource, ANImageID* pImageIDPtr);
	bool GetImageSize(ANImageID ImageID, anVec2* pSize);
	void FreeImage(ANImageID ImageID);
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
	void PushFontAppierence(FontAppierence Appierence);
	void PopFontAppierence();
private:
	ANCore* m_pCore;

	IANRendererBackend* m_pRendererBackend;

	ANWindowHandle m_Window;

	bool m_bEnableVerticalSync;

	ANInternalGuiWindowID m_CurrentWindowID;
	anVec2 m_CurrentWindowIDPos;
	anVec2 m_CurrentWindowIDSize;
	anRect m_CurrentWindowIDRect;

	ANFontID m_FontIDDefault;
	ANFontID m_FontID;
	FontAppierence m_FontAppierence;

	bool CreateBackendRender();
	bool CreateDefaultFont();

	bool CheckObjectIsGuiWindowScoped(anVec2 Pos);
};
