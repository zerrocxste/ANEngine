#include "ANEngine.h"

ANCore::ANCore() : 
	m_pANWindow(new ANWindow("Game", anvec2(100.f, 100.f), anvec2(300.f, 300.f), false))
{
	auto w = GetWindow();

	if (w->MakeWindow())
	{
		w->WindowShow();
	}
}

ANCore::~ANCore()
{

}

ANWindow* ANCore::GetWindow()
{
	return this->m_pANWindow;
}
