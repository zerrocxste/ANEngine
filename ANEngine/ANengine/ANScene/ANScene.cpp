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

	w->WindowShow();

	auto r = this->m_pCore->GetRenderer();

	auto g = this->m_pCore->GetGame();

	auto i = this->m_pCore->GetInput();

	while (w->ProcessWindow())
	{
		if (!w->IsAllowRender())
			continue;

		if (!r->PrepareScene())
			continue;

		r->BeginFrame();

		r->ClearScene();
		
		i->Update();

		g->RunScene();

		r->EndFrame();
	}

	return true;
}
