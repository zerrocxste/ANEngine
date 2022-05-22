#include "../ANEngine.h"

ANGame::ANGame(ANCore* pCore) :
	IANError(),
	m_pCore(pCore),
	m_pCurrentScene(nullptr),
	m_bNeedLeaveGame(false)
{
	this->m_pEntityList = ANMemory::GetInstance()->Allocate<ANEntityList>();
}

ANGame::~ANGame()
{
	ANMemory::GetInstance()->Delete(this->m_pEntityList);
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

	GetEntityList()->Clear();

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

	this->m_pCore->GetApi()->Update();

	return true;
}

void ANGame::LeaveGame()
{
	this->m_bNeedLeaveGame = true;
}

void ANGame::RegWorld(IANWorld** ppWorld)
{
	auto& pWorld = *ppWorld;

	pWorld = ANMemory::GetInstance()->Allocate<ANWorld>();

	pWorld->m_pIANAnimationCompositionController = ANMemory::GetInstance()->Allocate<ANAnimationCompositionController>();
}

void ANGame::UnregWorld(IANWorld** ppWorld)
{
	auto& pWorld = *ppWorld;

	if (!pWorld)
		return;

	ANMemory::GetInstance()->Delete(pWorld->m_pIANAnimationCompositionController);

	ANMemory::GetInstance()->Delete(pWorld);

	pWorld = nullptr;
}

void ANGame::RegEntity(IANEntity** ppEntity, const char* pszEntityClassID)
{
	auto& pEntity = *ppEntity;

	pEntity = ANMemory::GetInstance()->Allocate<ANEntity>();

	pEntity->m_pIANAnimationCompositionController = ANMemory::GetInstance()->Allocate<ANAnimationCompositionController>();

	if (pszEntityClassID)
	{
		auto LengthEntityName = strlen(pszEntityClassID) + 1;
		memcpy(((ANEntity*)pEntity)->m_szEntityClassID = new char[LengthEntityName], pszEntityClassID, LengthEntityName);
	}

	GetEntityList()->Add(*ppEntity);
}

void ANGame::UnregEntity(IANEntity** ppEntity)
{
	auto& pEntity = *ppEntity;

	if (!pEntity)
		return;

	GetEntityList()->Remove(pEntity);

	ANMemory::GetInstance()->Delete(pEntity->m_pIANAnimationCompositionController);

	ANMemory::GetInstance()->Delete(pEntity);

	pEntity = nullptr;
}

ANEntityList* ANGame::GetEntityList()
{
	return this->m_pEntityList;
}
