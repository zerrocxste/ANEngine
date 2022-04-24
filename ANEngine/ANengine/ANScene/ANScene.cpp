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

	w->WindowShow();

	auto g = this->m_pCore->GetGame();

	while (w->ProcessWindow())
	{
		if (!w->IsAllowRender())
			continue;

		if (!r->PrepareScene())
			continue;

		r->BeginFrame();

		r->ClearScene();

		g->RunScene();

		r->EndFrame();
	}

	return true;
}
