#include "../../ANEngine.h"

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
	if (!GuiWindow)
		return false;

	ANGuiWindow* gw = (ANGuiWindow*)GuiWindow;

	anVec2 CurrentWindowSize;

	this->m_pCore->GetRenderer()->GetGuiWindowSize(gw->m_InternalGuiWindowID, &CurrentWindowSize);

	if (gw->m_Size != CurrentWindowSize)
		this->m_pCore->GetRenderer()->SetGuiWindowSize(&gw->m_InternalGuiWindowID, gw->m_Size);

	return this->m_pCore->GetRenderer()->BeginGuiWindow(gw->m_InternalGuiWindowID, Pos, gw->m_Size);
}

void ANGui::WindowEnd()
{
	this->m_pCore->GetRenderer()->DrawGuiWindow();
	this->m_pCore->GetRenderer()->EndGuiWindow();
}

bool ANGui::WindowGetSize(ANGuiWindowID GuiWindow, anVec2* pSize)
{
	ANGuiWindow* gw = (ANGuiWindow*)(GuiWindow);
	return this->m_pCore->GetRenderer()->GetGuiWindowSize(gw->m_InternalGuiWindowID, pSize);
}

bool ANGui::WindowResize(ANGuiWindowID* pGuiWindow, anVec2 Size)
{
	ANGuiWindow* gw = (ANGuiWindow*)(*pGuiWindow);
	gw->m_Size = Size;
	return true;
}

bool ANGui::Button(const char* pszName, anVec2 Pos, anVec2 Size, IANGuiButtonSkin* pButtonSkin)
{
	auto LineWidth = 5;

	auto Rect = anRect(Pos, Pos + Size);

	auto i = this->m_pCore->GetInput();
	auto r = this->m_pCore->GetRenderer();

	auto CursorPos = i->GetCursorPos();
	auto IsPressed = i->IsCursorKeyDowned(CursorKey::MAIN_FIRST);
	auto IsClicked = i->IsCursorKeyReleased(CursorKey::MAIN_FIRST);
	auto IsHovered = Rect.IsIntersected(CursorPos);

	anColor bgColor = IsHovered ? IsPressed ? anColor::Blue() : anColor::Green() : anColor::Aqua();

	ANImageID ImageBG = 0;

	if (pButtonSkin != nullptr)
		pButtonSkin->SetSkin(IsHovered, IsPressed, IsClicked, &Rect, &bgColor, &ImageBG);

	if (ImageBG == 0)
		r->DrawFilledRectangle(Pos, Size, bgColor);
	else
		r->DrawImage(ImageBG, Rect, bgColor.a / 255.f);

	anVec2 TextSize;
	r->TextCalcSize(pszName, &TextSize);

	r->TextDraw(pszName, anVec2(Pos.x + (Size.x / 2.f) - (TextSize.x / 2.f), Pos.y + (Size.y / 2.f) - (TextSize.y / 2.f)), anColor::Black());

	auto ret = IsHovered && IsClicked;

	return ret;
}

bool ANGui::Checkbox(const char* pszName, anVec2 Pos, anVec2 Size, bool* pVar, IANCheckboxSkin* pCheckboxSkin)
{
	auto LineWidth = 5;

	auto bgRect = anRect(Pos, Pos + Size);

	auto i = this->m_pCore->GetInput();
	auto r = this->m_pCore->GetRenderer();

	auto CursorPos = i->GetCursorPos();
	auto IsPressed = i->IsCursorKeyDowned(CursorKey::MAIN_FIRST);
	auto IsClicked = i->IsCursorKeyReleased(CursorKey::MAIN_FIRST);
	auto IsHovered = bgRect.IsIntersected(CursorPos);

	auto MarkPos = Pos + LineWidth;
	auto MarkSize = Size - (LineWidth * 2.f);
	auto markRect = anRect(MarkPos, MarkPos + MarkSize);

	anColor bgColor = IsHovered ? IsPressed ? anColor::Blue() : anColor::Green() : anColor::Aqua(), markColor = anColor::Red();

	ANImageID ImageBG = 0, ImageMark = 0;

	if (pCheckboxSkin != nullptr)
		pCheckboxSkin->SetSkin(IsHovered, IsPressed, IsClicked, &bgRect, &bgColor, &ImageBG, &markRect, &markColor, &ImageMark);

	if (ImageBG == 0)
		r->DrawFilledRectangle(bgRect, bgColor);
	else
		r->DrawImage(ImageBG, bgRect, bgColor.a / 255.f);

	if (*pVar)
	{
		if (ImageMark == 0)
			r->DrawFilledRectangle(markRect, markColor);
		else
			r->DrawImage(ImageMark, markRect, markColor.a / 255.f);
	}

	anVec2 TextSize;
	r->TextCalcSize(pszName, &TextSize);
	r->TextDraw(pszName, anVec2(Pos.x + Size.x + 5.f, Pos.y + ((Size.y * 0.5f) - (TextSize.y * 0.5f))), anColor::Black());

	auto ret = IsHovered && IsClicked;
		
	if (ret)
		*pVar = !*pVar;

	return ret;
}

bool ANGui::SliderInt(const char* pszName, anVec2 Pos, anVec2 Size, int iMin, int iMax, int* pVar, IANSliderSkin* pSliderSkin)
{
	auto LineWidth = 5;
	auto SliderMarkWidth = 10;

	auto i = this->m_pCore->GetInput();
	auto r = this->m_pCore->GetRenderer();

	anVec2 TextSize;
	r->TextCalcSize(pszName, &TextSize);
	auto TextPos = Pos;

	Pos.y += TextSize.y + 5.f;

	auto bgRect = anRect(Pos, Pos + Size);

	auto SliderPos = anVec2(Pos.x + LineWidth + SliderMarkWidth, Pos.y + LineWidth);
	auto SliderSize = anVec2(Size.x - ((LineWidth + SliderMarkWidth) * 2.f), Size.y - (LineWidth * 2.f));
	auto CurrentSliderValue = ANMathUtils::LinearInterpolation(iMin, *pVar, iMax, 0.f, SliderSize.x);
	auto sliderRect = anRect(SliderPos, SliderPos + SliderSize);

	auto CursorPos = i->GetCursorPos();
	auto IsHovered = bgRect.IsIntersected(CursorPos);
	auto IsPressed = i->IsCursorKeyDowned(CursorKey::MAIN_FIRST);
	auto IsClicked = i->IsCursorKeyReleased(CursorKey::MAIN_FIRST);

	anColor bgColor = IsHovered ? IsPressed ? anColor::Blue() : anColor::Green() : anColor::Aqua(), sliderMarkColor = anColor::Red();

	ANImageID ImageBG = 0, ImageMark = 0;

	auto MarkPos = anVec2(SliderPos.x + CurrentSliderValue - SliderMarkWidth, SliderPos.y);
	auto MarkSize = anVec2(SliderMarkWidth * 2.f, SliderSize.y);
	auto markRect = anRect(MarkPos, MarkPos + MarkSize);

	if (pSliderSkin != nullptr)
		pSliderSkin->SetSkin(IsHovered, IsPressed, IsClicked, &bgRect, &bgColor, &ImageBG, &markRect, &sliderMarkColor, &ImageMark);

	auto ret = IsHovered && IsPressed;

	if (ret)
	{
		CurrentSliderValue = ANMathUtils::Clamp(CursorPos.x - SliderPos.x, 0.f, SliderSize.x);
		*pVar = ANMathUtils::LinearInterpolation(0.f, CurrentSliderValue, SliderSize.x, iMin, iMax);;
	}
	
	if (ImageBG == 0)
		r->DrawFilledRectangle(bgRect, bgColor);
	else
		r->DrawImage(ImageBG, bgRect, bgColor.a / 255.f);

	if (ImageMark == 0)
		r->DrawFilledRectangle(markRect, sliderMarkColor);
	else
		r->DrawImage(ImageMark, markRect, bgColor.a / 255.f);

	r->TextDraw(pszName, anVec2(TextPos.x + 5.f, TextPos.y), anColor::Black());

	return ret;
}

bool ANGui::SliderFloat(const char* pszName, anVec2 Pos, anVec2 Size, float flMin, float flMax, float* pVar, IANSliderSkin* pSliderSkin)
{
	auto LineWidth = 5;
	auto SliderMarkWidth = 10;

	auto i = this->m_pCore->GetInput();
	auto r = this->m_pCore->GetRenderer();

	anVec2 TextSize;
	r->TextCalcSize(pszName, &TextSize);
	auto TextPos = Pos;

	Pos.y += TextSize.y + 5.f;

	auto bgRect = anRect(Pos, Pos + Size);

	auto SliderPos = anVec2(Pos.x + LineWidth + SliderMarkWidth, Pos.y + LineWidth);
	auto SliderSize = anVec2(Size.x - ((LineWidth + SliderMarkWidth) * 2.f), Size.y - (LineWidth * 2.f));
	auto CurrentSliderValue = ANMathUtils::LinearInterpolation(flMin, *pVar, flMax, 0.f, SliderSize.x);
	auto sliderRect = anRect(SliderPos, SliderPos + SliderSize);

	auto CursorPos = i->GetCursorPos();
	auto IsHovered = bgRect.IsIntersected(CursorPos);
	auto IsPressed = i->IsCursorKeyDowned(CursorKey::MAIN_FIRST);
	auto IsClicked = i->IsCursorKeyReleased(CursorKey::MAIN_FIRST);

	anColor bgColor = IsHovered ? IsPressed ? anColor::Blue() : anColor::Green() : anColor::Aqua(), sliderMarkColor = anColor::Red();

	ANImageID ImageBG = 0, ImageMark = 0;

	auto MarkPos = anVec2(SliderPos.x + CurrentSliderValue - SliderMarkWidth, SliderPos.y);
	auto MarkSize = anVec2(SliderMarkWidth * 2.f, SliderSize.y);
	auto markRect = anRect(MarkPos, MarkPos + MarkSize);

	if (pSliderSkin != nullptr)
		pSliderSkin->SetSkin(IsHovered, IsPressed, IsClicked, &bgRect, &bgColor, &ImageBG, &markRect, &sliderMarkColor, &ImageMark);

	auto ret = IsHovered && IsPressed;

	if (ret)
	{
		CurrentSliderValue = ANMathUtils::Clamp(CursorPos.x - SliderPos.x, 0.f, SliderSize.x);
		*pVar = ANMathUtils::LinearInterpolation(0.f, CurrentSliderValue, SliderSize.x, flMin, flMax);;
	}

	if (ImageBG == 0)
		r->DrawFilledRectangle(bgRect, bgColor);
	else
		r->DrawImage(ImageBG, bgRect, bgColor.a / 255.f);

	if (ImageMark == 0)
		r->DrawFilledRectangle(markRect, sliderMarkColor);
	else
		r->DrawImage(ImageMark, markRect, bgColor.a / 255.f);

	r->TextDraw(pszName, anVec2(TextPos.x + 5.f, TextPos.y), anColor::Black());

	return ret;
}
