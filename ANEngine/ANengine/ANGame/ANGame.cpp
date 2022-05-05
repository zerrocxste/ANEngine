#include "../ANEngine.h"

ANGame::ANGame(ANCore* pCore) :
	IANError(),
	m_pCore(pCore),
	m_pCurrentScene(nullptr)
{

}

ANGame::~ANGame()
{

}

bool ANGame::ConnectScene(IANGameScene* pScene)
{
	if (!pScene)
		return false;

	DisconnectScene();

	this->m_pCurrentScene = pScene;

	this->m_pCurrentScene->OnLoadScene(this->m_pCore->GetApi());

	return true;
}

void ANGame::DisconnectScene()
{
	if (!this->m_pCurrentScene)
		return;

	this->m_pCurrentScene->OnUnloadScene(this->m_pCore->GetApi());
}

bool ANGame::RunScene()
{
	if (!this->m_pCurrentScene)
	{
		auto r = this->m_pCore->GetRenderer();
		anVec2 Size;
		r->TextCalcSize("NO_SCENE", &Size);
		r->TextDraw("NO_SCENE", ANMathUtils::CalcPosToCenter(r->GetScreenSize(), Size), anColor::Red());
		return false;
	}

	this->m_pCore->GetApi()->Update();

	this->m_pCurrentScene->Entry(this->m_pCore->GetApi());

	return true;
}