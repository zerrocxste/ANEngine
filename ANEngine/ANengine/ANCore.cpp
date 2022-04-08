#include "ANEngine.h"

ANCore::ANCore() : 
	m_pANWindow(new ANWindow("Game", anvec2(100.f, 100.f), anvec2(300.f, 300.f), true))
{
	
}

ANCore::~ANCore()
{

}

ANWindow* ANCore::GetWindow()
{
	return this->m_pANWindow;
}

bool ANCore::Run()
{
	auto w = GetWindow();

	if (!w->MakeWindow())
		return false;

	w->WindowShow();

	w->RunWindow();

	return true;
}