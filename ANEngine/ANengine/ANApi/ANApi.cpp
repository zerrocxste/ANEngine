#include "../ANEngine.h"

ANApi::ANApi(ANCore* pCore) : 
	IANApi(),
	m_pCore(pCore)
{
	this->FPS = 0;
	this->Frametime = 0.;
	this->ScreenSize.x = this->ScreenSize.y = 0.f;
}

ANApi::~ANApi()
{

}

bool ANApi::CreateImage(const char* pszPath, ANImageID* pImageID)
{
	ANUniqueResource ImageResource;

	if (!this->m_pCore->GetResourceManager()->ReadBinFile(pszPath, &ImageResource))
		return false;

	return this->m_pCore->GetRenderer()->CreateImageFromResource(&ImageResource, pImageID);
}

void ANApi::FreeImage(ANImageID* pImageIDPtr)
{
	this->m_pCore->GetRenderer()->FreeImage(pImageIDPtr);
}

bool ANApi::DrawImage(ANImageID pImageID, anVec2 Pos, anVec2 Size, float Opacity)
{
	return this->m_pCore->GetRenderer()->DrawImage(pImageID, Pos, Size, Opacity);
}

bool ANApi::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float Rounding, bool Filled)
{
	auto r = this->m_pCore->GetRenderer();

	return Filled ? r->DrawFilledRectangle(Pos, Size, Color, Rounding) : r->DrawRectangle(Pos, Size, Color, Rounding);
}

bool ANApi::DrawCircle(anVec2 Pos, anColor Color, float Radius, bool Filled)
{
	auto r = this->m_pCore->GetRenderer();

	return Filled ? r->DrawFilledCircle(Pos, Color, Radius) : r->DrawCircle(Pos, Color, Radius);
}

bool ANApi::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID)
{
	return this->m_pCore->GetRenderer()->CreateFontFromFile(pszPath, FontSize, pFontID);
}

void ANApi::FreeFont(ANFontID* pFontIDPtr)
{
	this->m_pCore->GetRenderer()->FreeFont(pFontIDPtr);
}

bool ANApi::TextDraw(const char* pszText, anVec2 Pos, anColor Color, ANFontID pFont)
{
	return this->m_pCore->GetRenderer()->TextDraw(pszText, Pos, Color, pFont);
}

void ANApi::Update()
{
	auto r = this->m_pCore->GetRenderer();

	this->FPS = r->GetFramePerSecond();
	this->Frametime = r->GetFrameTime();
	this->ScreenSize = r->GetScreenSize();
}
