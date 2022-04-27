#include "../ANEngine.h"

ANApi::ANApi(ANCore* pCore) : 
	IANApi(),
	m_pCore(pCore)
{
	this->FPS = 0;
	this->Frametime = 0.;
}

ANApi::~ANApi()
{

}

anVec2 ANApi::GetScreenSize()
{
	return this->m_pCore->GetRenderer()->GetScreenSize();
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

bool ANApi::DrawLine(anVec2 From, anVec2 To, anColor Color, float LineThickness)
{
	return this->m_pCore->GetRenderer()->DrawLine(From, To, Color, LineThickness);
}

bool ANApi::DrawRectangle(anVec2 Pos, anVec2 Size, anColor Color, float LineThickness, float Rounding, bool Filled)
{
	auto r = this->m_pCore->GetRenderer();

	return Filled ? r->DrawFilledRectangle(Pos, Size, Color, Rounding) : r->DrawRectangle(Pos, Size, Color, LineThickness, Rounding);
}

bool ANApi::DrawTrinagle(anVec2 pt1, anVec2 pt2, anVec2 pt3, anColor Color, float LineThickness, bool Filled)
{
	return Filled ? this->m_pCore->GetRenderer()->DrawFilledTrinagle(pt1, pt2, pt3, Color) : this->m_pCore->GetRenderer()->DrawTrinagle(pt1, pt2, pt3, Color, LineThickness);
}

bool ANApi::DrawCircle(anVec2 Pos, anColor Color, float Radius, float LineThickness, bool Filled)
{
	auto r = this->m_pCore->GetRenderer();

	return Filled ? r->DrawFilledCircle(Pos, Color, Radius) : r->DrawCircle(Pos, Color, Radius, LineThickness);
}

bool ANApi::CreateFontFromFile(const char* pszPath, float FontSize, ANFontID* pFontID)
{
	return this->m_pCore->GetRenderer()->CreateFontFromFile(pszPath, FontSize, pFontID);
}

void ANApi::FreeFont(ANFontID* pFontIDPtr)
{
	this->m_pCore->GetRenderer()->FreeFont(pFontIDPtr);
}

void ANApi::PushFont(ANFontID FontID)
{
	this->m_pCore->GetRenderer()->PushFont(FontID);
}

void ANApi::PopFont()
{
	this->m_pCore->GetRenderer()->PopFont();
}

bool ANApi::TextDraw(const char* pszText, anVec2 Pos, anColor Color)
{
	return this->m_pCore->GetRenderer()->TextDraw(pszText, Pos, Color);
}

bool ANApi::RegGuiWindow(ANGuiWindowID* pGuiWindowID, anVec2 Size)
{
	return this->m_pCore->GetGui()->WindowCreate(pGuiWindowID, Size);
}

bool ANApi::UnregGuiWindow(ANGuiWindowID* pGuiWindowID)
{
	return this->m_pCore->GetGui()->WindowDelete(pGuiWindowID);
}

bool ANApi::BeginGuiWindow(ANGuiWindowID GuiWindow, anVec2 Pos)
{
	return this->m_pCore->GetGui()->WindowBegin(GuiWindow, Pos);
}

void ANApi::EndGuiWindow()
{
	this->m_pCore->GetGui()->WindowEnd();
}

anVec2 ANApi::GetCurrentWindowSize()
{
	return this->m_pCore->GetRenderer()->GetCurrentWindowSize();
}

bool ANApi::AddCheckbox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar)
{
	return this->m_pCore->GetGui()->CheckBox(pszName, Pos, Size, pVar);
}

bool ANApi::AddSliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar)
{
	return this->m_pCore->GetGui()->SliderInt(pszName, Pos, Size, iMin, iMax, pVar);
}

bool ANApi::AddSliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar)
{
	return this->m_pCore->GetGui()->SliderFloat(pszName, Pos, Size, flMin, flMax, pVar);
}

void ANApi::Update()
{
	auto r = this->m_pCore->GetRenderer();

	this->FPS = r->GetFramePerSecond();
	this->Frametime = r->GetFrameTime();
}
