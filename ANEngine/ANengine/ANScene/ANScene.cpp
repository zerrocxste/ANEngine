#include "../ANEngine.h"

ANScene::ANScene(ANCore* pCore) :
	IANError(),
	m_pCore(pCore)
{

}

ANScene::~ANScene()
{

}

bool ANScene::Run()
{
	auto w = this->m_pCore->GetWindow();
	auto r = this->m_pCore->GetRenderer();
	auto g = this->m_pCore->GetGame();
	auto i = this->m_pCore->GetInput();
	auto p = this->m_pCore->GetPerfomance();

	w->WindowShow();

	while (w->ProcessWindow())
	{
		if (!w->IsAllowRender())
			continue;

		if (!p->PrepareScene())
			continue;

		r->BeginFrame();

		r->ClearScene();
		
		i->Update();

		g->RunScene();

		r->EndFrame();

		p->Update();
	}

	return true;
}
