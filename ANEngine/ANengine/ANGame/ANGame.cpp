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
	*ppWorld = ANMemory::GetInstance()->Allocate<ANWorld>();
}

void ANGame::UnregWorld(IANWorld** ppWorld)
{
	if (!*ppWorld)
		return;

	ANMemory::GetInstance()->Delete(*ppWorld);

	*ppWorld = nullptr;
}

void ANGame::RegEntity(IANEntity** ppEntity, const char* pszEntityClassID)
{
	*ppEntity = ANMemory::GetInstance()->Allocate<ANEntity>();

	if (pszEntityClassID)
	{
		auto LengthEntityName = strlen(pszEntityClassID) + 1;
		memcpy(((ANEntity*)(*ppEntity))->m_szEntityClassID = new char[LengthEntityName], pszEntityClassID, LengthEntityName);
	}

	GetEntityList()->Add(*ppEntity);
}

void ANGame::UnregEntity(IANEntity** ppEntity)
{
	if (!*ppEntity)
		return;

	GetEntityList()->Remove(*ppEntity);

	ANMemory::GetInstance()->Delete(*ppEntity);

	*ppEntity = nullptr;
}

ANEntityList* ANGame::GetEntityList()
{
	return this->m_pEntityList;
}
