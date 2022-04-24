#include "../ANEngine.h"

ANGui::ANGui(ANCore* pCore) : 
	m_pCore(pCore)
{

}

ANGui::~ANGui()
{

}

bool ANGui::CheckBox(const char* pszName, bool* pVar)
{
	auto i = this->m_pCore->GetInput();

	auto IsClicked = i->GetCursorKey(CursorKey::MAIN_FIRST);

	auto LineWidth = 5;

	anVec2 Pos = anVec2(120.f, 120.f);
	anVec2 Size = anVec2(120.f, 120.f);
	
	auto IsHovered = anRect(Pos, Pos + Size).IsIntersected(i->GetCursorPos());

	this->m_pCore->GetRenderer()->DrawRectangle(Pos, Size, anColor::Red(), LineWidth);

	auto Color = IsHovered ? IsClicked ? anColor::Blue() : anColor::Green() : anColor::Black();

	this->m_pCore->GetRenderer()->DrawFilledRectangle(Pos + LineWidth, Size - (LineWidth * 2.f), Color);

	auto ret = IsHovered && IsClicked;
		
	if (ret) // kak eto blyat sdelat
	{
		*pVar = !*pVar;
	}

	return ret;
}
