#include "../ANEngine.h"

ANGui::ANGui(ANCore* pCore) : 
	m_pCore(pCore)
{
	
}

ANGui::~ANGui()
{

}

bool ANGui::WindowCreate(ANGuiWindowID* pGuiWindow, anVec2 Size)
{
	*pGuiWindow = 0;

	auto gw = ANMemory::GetInstance()->Allocate<ANGuiWindow>(Size);

	auto ret = this->m_pCore->GetRenderer()->CreateGuiWindow(&gw->m_InternalGuiWindowID, Size);

	if (ret)
		*pGuiWindow = (ANGuiWindowID*)gw;

	return ret;
}

bool ANGui::WindowDelete(ANGuiWindowID* pGuiWindow)
{
	ANGuiWindow* gw = (ANGuiWindow*)*pGuiWindow;

	auto ret = this->m_pCore->GetRenderer()->DeleteGuiWindow(&gw->m_InternalGuiWindowID);

	ANMemory::GetInstance()->Delete(gw);

	return ret;
}

bool ANGui::WindowBegin(ANGuiWindowID GuiWindow, anVec2 Pos)
{
	ANGuiWindow* gw = (ANGuiWindow*)GuiWindow;

	return this->m_pCore->GetRenderer()->BeginGuiWindow(gw->m_InternalGuiWindowID, Pos, gw->m_Size);
}

void ANGui::WindowEnd()
{
	this->m_pCore->GetRenderer()->DrawGuiWindow();
	this->m_pCore->GetRenderer()->EndGuiWindow();
}

bool ANGui::CheckBox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar)
{
	auto LineWidth = 5;

	auto i = this->m_pCore->GetInput();
	auto r = this->m_pCore->GetRenderer();

	auto CursorPos = i->GetCursorPos();
	auto IsPressed = i->IsCursorKeyDowned(CursorKey::MAIN_FIRST);
	auto IsClicked = i->IsCursorKeyReleased(CursorKey::MAIN_FIRST);
	auto IsHovered = anRect(Pos, Pos + Size).IsIntersected(CursorPos);

	auto Color = IsHovered ? IsPressed ? anColor::Blue() : anColor::Green() : anColor::Aqua();
	r->DrawFilledRectangle(Pos, Size, Color);

	if (*pVar)
		r->DrawFilledRectangle(Pos + LineWidth, Size - (LineWidth * 2.f), anColor::Red());

	anVec2 TextSize;
	r->TextCalcSize(pszName, &TextSize);
	auto TextPos = anVec2(Pos.x + Size.x + 5.f, Pos.y + ((Size.y * 0.5f) - (TextSize.y * 0.5f)));
	r->TextDraw(pszName, TextPos, anColor::Black());

	auto ret = IsHovered && IsClicked;
		
	if (ret)
		*pVar = !*pVar;

	return ret;
}

bool ANGui::SliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar)
{
	auto LineWidth = 5;

	auto i = this->m_pCore->GetInput();
	auto r = this->m_pCore->GetRenderer();

	auto CursorPos = i->GetCursorPos();
	auto IsPressed = i->IsCursorKeyDowned(CursorKey::MAIN_FIRST);
	auto IsClicked = i->IsCursorKeyReleased(CursorKey::MAIN_FIRST);

	anVec2 TextSize;
	r->TextCalcSize(pszName, &TextSize);
	r->TextDraw(pszName, anVec2(Pos.x + 5.f, Pos.y), anColor::Black());

	Pos.y += TextSize.y + 5.f;

	auto IsHovered = anRect(Pos, Pos + Size).IsIntersected(CursorPos);

	auto Color = IsHovered ? IsPressed ? anColor::Blue() : anColor::Green() : anColor::Aqua();

	r->DrawFilledRectangle(Pos, Size, Color);

	auto SliderPos = Pos + LineWidth;
	auto SliderSize = Size - (LineWidth * 2.f);

	auto CurrentSliderValue = ANMathUtils::LinearInterpolation(iMin, *pVar, iMax, 0.f, SliderSize.x);

	auto ret = IsHovered && IsPressed;

	if (ret)
	{
		CurrentSliderValue = ANMathUtils::Clamp(CursorPos.x - SliderPos.x, 0.f, SliderSize.x);
		*pVar = ANMathUtils::LinearInterpolation(0.f, CurrentSliderValue, SliderSize.x, iMin, iMax);;
	}

	r->DrawFilledRectangle(SliderPos, anVec2(CurrentSliderValue, SliderSize.y), anColor::Red());

	return ret;
}

bool ANGui::SliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar)
{
	auto LineWidth = 5;

	auto i = this->m_pCore->GetInput();
	auto r = this->m_pCore->GetRenderer();

	auto CursorPos = i->GetCursorPos();
	auto IsPressed = i->IsCursorKeyDowned(CursorKey::MAIN_FIRST);
	auto IsClicked = i->IsCursorKeyReleased(CursorKey::MAIN_FIRST);

	anVec2 TextSize;
	r->TextCalcSize(pszName, &TextSize);
	r->TextDraw(pszName, anVec2(Pos.x + 5.f, Pos.y), anColor::Black());

	Pos.y += TextSize.y + 5.f;

	auto IsHovered = anRect(Pos, Pos + Size).IsIntersected(CursorPos);

	auto Color = IsHovered ? IsPressed ? anColor::Blue() : anColor::Green() : anColor::Aqua();

	r->DrawFilledRectangle(Pos, Size, Color);

	auto SliderPos = Pos + LineWidth;
	auto SliderSize = Size - (LineWidth * 2.f);

	auto CurrentSliderValue = ANMathUtils::LinearInterpolation(flMin, *pVar, flMax, 0.f, SliderSize.x);

	auto ret = IsHovered && IsPressed;

	if (ret)
	{
		CurrentSliderValue = ANMathUtils::Clamp(CursorPos.x - SliderPos.x, 0.f, SliderSize.x);
		*pVar = ANMathUtils::LinearInterpolation(0.f, CurrentSliderValue, SliderSize.x, flMin, flMax);
	}

	this->m_pCore->GetRenderer()->DrawFilledRectangle(SliderPos, anVec2(CurrentSliderValue, SliderSize.y), anColor::Red());

	return ret;
}
