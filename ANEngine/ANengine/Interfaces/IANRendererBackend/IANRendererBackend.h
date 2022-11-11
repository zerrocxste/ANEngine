#pragma once

class IANRendererBackend : public IANError
{
public:
	virtual bool InitializeRenderer(ANWindowHandle WindowHandle, bool bEnableVerticalSync, void* pReversed) = 0;

	virtual bool BeginFrame() = 0;
	virtual bool EndFrame() = 0;
	virtual bool ClearScene() = 0;
	virtual bool ResetScene(anVec2 ScreenSize) = 0;
	virtual bool GetScreenSize(ANInternalGuiWindowID GuiWindow, anVec2* pAnvec2Out) = 0;
	virtual bool CreateImageFromMemory(void* pImageSrc, std::uint32_t iImageSize, ANImageID* pImageIDPtr) = 0;
	virtual bool GetImageSize(ANImageID ImageID, anVec2* pSize) = 0;
	virtual void FreeImage(ANImageID ImageID) = 0;
	virtual bool DrawImage(ANInternalGuiWindowID GuiWindow, ANImageID pImageID, anRect Pos, float Opacity) = 0;
	virtual bool DrawLine(ANInternalGuiWindowID GuiWindow, anVec2 From, anVec2 To, anColor Color, float LineThickness) = 0;
	virtual bool DrawRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float LineThickness, float Rounding) = 0;
	virtual bool DrawFilledRectangle(ANInternalGuiWindowID GuiWindow, anRect Pos, anColor Color, float Rounding) = 0;
	virtual bool DrawCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius, float LineThickness) = 0;
	virtual bool DrawTrinagle(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness) = 0;
	virtual bool DrawTrinagleFilled(ANInternalGuiWindowID GuiWindow, anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color) = 0;
	virtual bool DrawFilledCircle(ANInternalGuiWindowID GuiWindow, anVec2 Pos, anColor Color, float Radius) = 0;
	virtual bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontIDPtr) = 0;
	virtual void FreeFont(ANFontID* pFontIDPtr) = 0;
	virtual bool TextCalcSize(const char* pszText, ANFontID FontID, anVec2* pTextSize) = 0;
	virtual bool TextDraw(ANInternalGuiWindowID GuiWindow, const char* pszText, anVec2 Pos, anColor Color, ANFontID FontID, FontAppierence Appierence) = 0;
	virtual bool CreateGuiWindow(ANInternalGuiWindowID* pGuiWindow, anVec2 Size) = 0;
	virtual bool DeleteGuiWindow(ANInternalGuiWindowID* GuiWindow) = 0;
	virtual bool BeginGuiWindow(ANInternalGuiWindowID GuiWindow) = 0;
	virtual bool EndGuiWindow(ANInternalGuiWindowID GuiWindow) = 0;
	virtual bool GetGuiWindowSize(ANInternalGuiWindowID GuiWindow, anVec2* pWindowSize) = 0;
	virtual bool ResizeGuiWindow(ANInternalGuiWindowID* GuiWindow, anVec2 WindowSize) = 0;
	virtual bool DrawGuiWindow(ANInternalGuiWindowID GuiWindow, anVec2 Pos) = 0;
};