#include "ANEngine.h"

ANCore::ANCore()
{
	m_Interfaces.m_pANWindow = new ANWindow("Game", anvec2(100.f, 100.f), anvec2(300.f, 300.f), true);
	m_Interfaces.m_pANInput = new ANInput();
	m_Interfaces.m_ANRenderer = new ANRenderer(RenderTypes::D3D9);
}

ANCore::~ANCore()
{

}

ANWindow* ANCore::GetWindow()
{
	assert(this->m_Interfaces.m_pANWindow != nullptr);
	return this->m_Interfaces.m_pANWindow;
}

ANInput* ANCore::GetInput()
{
	assert(this->m_Interfaces.m_pANInput != nullptr);
	return this->m_Interfaces.m_pANInput;
}

ANRenderer* ANCore::GetRenderer()
{
	assert(this->m_Interfaces.m_ANRenderer != nullptr);
	return this->m_Interfaces.m_ANRenderer;
}

bool ANCore::Run()
{
	auto w = GetWindow();

	if (!w->MakeWindow())
	{
		MessageBox(0, w->What(), "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	auto r = GetRenderer();

	if (!r->Initalize(w->GetHWND()))
	{
		MessageBox(0, r->What(), "Error", MB_ICONERROR | MB_OK);
		return false;
	}

	w->WindowShow();

	w->RunWindow();

	return true;
}

ANCore* ANCore::GetInstance()
{
	static auto Ptr = new ANCore();
	return Ptr;
}
