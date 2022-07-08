#include "../ANEngine.h"

ANGame::ANGame(ANCore* pCore) :
	IANError(),
	m_pCore(pCore),
	m_pCurrentScene(nullptr),
	m_bNeedLeaveGame(false)
{
	this->m_pEntityList = ANMemory::GetInstance()->Allocate<ANEntityList>();
	this->m_pInteractionMessagesList = ANMemory::GetInstance()->Allocate<ANInteractionMessagesList>();
}

ANGame::~ANGame()
{
	ANMemory::GetInstance()->Delete(this->m_pEntityList);
	ANMemory::GetInstance()->Delete(this->m_pInteractionMessagesList);
}

bool ANGame::ConnectScene(IANGameScene* pScene)
{
	if (!pScene)
		return false;

	if (!this->m_pCurrentScene)
	{
		this->m_pCurrentScene = pScene;
		this->m_pCurrentScene->OnLoadScene(this->m_pCore->GetApi());
	}
	else
		this->m_pNewGameScene = pScene;

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
	if (this->m_bNeedLeaveGame)
		return false;

	if (!this->m_pCurrentScene)
	{
		auto r = this->m_pCore->GetRenderer();
		anVec2 Size;
		r->TextCalcSize("NO_SCENE", &Size);
		r->TextDraw("NO_SCENE", ANMathUtils::CalcPosToCenter(r->GetScreenSize(), Size), anColor::Red());
		return true;
	}

	this->m_pCurrentScene->Entry(this->m_pCore->GetApi());

	if (this->m_pNewGameScene != nullptr)
	{
		DisconnectScene();
		this->m_pCurrentScene = this->m_pNewGameScene;
		this->m_pCurrentScene->OnLoadScene(this->m_pCore->GetApi());
		this->m_pNewGameScene = nullptr;
	}

	this->m_pCore->GetApi()->Update();

	return true;
}

void ANGame::LeaveGame()
{
	this->m_bNeedLeaveGame = true;
}

void ANGame::RegWorld(IANWorld** ppWorld)
{
	auto& pWorld = (*ppWorld) = ANMemory::GetInstance()->Allocate<ANWorld>();

	((ANWorld*)pWorld)->m_pIANAnimationCompositionController = ANMemory::GetInstance()->Allocate<ANAnimationCompositionController>();
}

void ANGame::UnregWorld(IANWorld** ppWorld)
{
	auto& pWorld = *ppWorld;

	if (!pWorld)
		return;

	ANMemory::GetInstance()->Delete(((ANWorld*)pWorld)->m_pIANAnimationCompositionController);

	ANMemory::GetInstance()->Delete(pWorld);

	pWorld = nullptr;
}

void ANGame::RegEntity(IANEntity** ppEntity, const char* pszEntityClassID)
{
	GetEntityList()->Reg(ppEntity, pszEntityClassID);

	GetEntityList()->Add(*ppEntity);
}

void ANGame::UnregEntity(IANEntity** ppEntity)
{
	auto& pIEntity = *ppEntity;

	if (!pIEntity)
		return;

	GetEntityList()->Unreg(pIEntity);

	GetEntityList()->Remove(pIEntity);

	pIEntity = nullptr;
}

ANEntityList* ANGame::GetEntityList()
{
	return this->m_pEntityList;
}

ANInteractionMessagesList* ANGame::GetInteractionList()
{
	return this->m_pInteractionMessagesList;
}
