#pragma once

class IANApi
{
public:
	int FPS;
	double Frametime;
	anVec2 ScreenSize;

	virtual bool CreateImage(const char* pszPath, ANImageID* pImageIDPtr) = 0;
	virtual void FreeImage(ANImageID* pImageIDPtr) = 0;
	virtual bool DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity) = 0;
	virtual bool DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness = 1.f) = 0;
	virtual bool DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness = 1.f, float Rounding = 0.f, bool Filled = false) = 0;
	virtual bool DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness = 1.f, bool Filled = false) = 0;
	virtual bool DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness = 1.f, bool Filled = false) = 0;
	virtual bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontIDPtr) = 0;
	virtual void FreeFont(ANFontID* pFontIDPtr) = 0;
	virtual bool TextDraw(const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont) = 0;

	virtual bool AddCheckbox(const char* pszName, bool* pVar) = 0;
};