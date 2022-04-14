#pragma once

class ANRenderer : public IANError
{
public:
	ANRenderer(ANCore* pCore, RenderTypes RenderType);
	~ANRenderer();

	bool Initalize(HWND hWnd);

	bool BeginFrame();
	bool EndFrame();
	bool ResetScene(WPARAM wParam, LPARAM lParam);
	anVec2 GetScreenSize();
	anRect InfiniteRect();

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

	HWND hWnd;

	ANRendererFuncionsTable* m_pANRendererFuncionsTable;

	RenderTypes m_RenderType;
	HWND m_hWnd;
	HMODULE m_RenderModule;

	bool LoadRendererModule();
	bool InvokeInitRender();
	bool InvokeInitFunctionTable();

	const char* RenderTypeToStr(RenderTypes RenderType);
};
