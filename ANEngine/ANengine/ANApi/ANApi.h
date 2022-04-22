#pragma once

class ANApi : public IANApi
{
	friend ANGame;
public:
	ANApi(ANCore* pCore);
	~ANApi();

	bool CreateImage(const char* pszPath, ANImageID* pImageID) override;
	void FreeImage(ANImageID* pImageIDPtr) override;
	bool DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity) override;
	bool DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding = 0.f, bool Filled = false) override;
	bool DrawCircle(anVec2 Pos, anColor Color, float Radius, bool Filled = false) override;
	bool CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID) override;
	void FreeFont(ANFontID* pFontIDPtr) override;
	bool TextDraw(const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont) override;
private:
	ANCore* m_pCore;

	void Update();
};