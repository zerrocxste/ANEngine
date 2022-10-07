#include "../ANEngine.h"

ANGame::ANGame(ANCore* pCore) :
	m_pCore(pCore),
	m_pNewGameScene(nullptr),
	m_pCurrentScene(nullptr),
	m_bNeedLeaveGame(false)
{
	this->m_pGameResourcesData = ANMemory::GetInstance()->Allocate<ANGameResourcesData>(this->m_pCore);
	this->m_pEntityList = ANMemory::GetInstance()->Allocate<ANEntityList>();
	this->m_pInteractionMessagesList = ANMemory::GetInstance()->Allocate<ANInteractionMessagesList>();
}

ANGame::~ANGame()
{
	ANMemory::GetInstance()->Delete(this->m_pGameResourcesData);
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

		anVec2 vecSizeNoScene, vecHelperMsg;
		auto pszNoSceneMsg = "NO SCENE\n";
		auto pszHelperMsg = "NEED CONNECT SCENE IN LOADER CTX\n";

		r->TextCalcSize(pszNoSceneMsg, &vecSizeNoScene);
		r->TextDraw(pszNoSceneMsg, ANMathUtils::CalcPosToCenter(r->GetScreenSize(), vecSizeNoScene), anColor::Red());

		r->TextCalcSize(pszHelperMsg, &vecHelperMsg);
		auto vecPosHelperMsg = ANMathUtils::CalcPosToCenter(r->GetScreenSize(), vecHelperMsg);
		vecPosHelperMsg.y += vecSizeNoScene.y;
		r->TextDraw(pszHelperMsg, vecPosHelperMsg, anColor::Red());

		return true;
	}

	for (auto& data : this->m_EveryFrameTask.m_vDefaultAnimationCompositionData)
	{
		auto pAnimationCompositionController = data.m_pEntity->GetAnimCompositionController();

		pAnimationCompositionController->SetAnimationComposition(data.m_AnimationComposition);
		pAnimationCompositionController->SetAnimationDuration(data.m_flAnimationDuration);
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

void ANGame::AddDefaultAnimationComposition(IANEntity* pEntity, ANAnimationComposition AnimationComposition, float flAnimationDuration)
{
	DeleteDefaultAnimationComposition(pEntity);

	auto& DefaultAnimationCompositionData = this->m_EveryFrameTask.m_vDefaultAnimationCompositionData;

	ANDefaultAnimationCompositionData data{};
	data.m_pEntity = pEntity;
	data.m_AnimationComposition = AnimationComposition;
	data.m_flAnimationDuration = flAnimationDuration;

	DefaultAnimationCompositionData.push_back(data);
}

void ANGame::DeleteDefaultAnimationComposition(IANEntity* pEntity)
{
	auto& DefaultAnimationCompositionData = this->m_EveryFrameTask.m_vDefaultAnimationCompositionData;

	for (auto it = DefaultAnimationCompositionData.begin(); it < DefaultAnimationCompositionData.end(); it++)
	{
		auto& data = *it;

		if (data.m_pEntity != pEntity)
			continue;

		it = DefaultAnimationCompositionData.erase(it);

		if (it == DefaultAnimationCompositionData.end())
			break;
	}
}

void ANGame::ClearDefaultAnimationComposition()
{
	this->m_EveryFrameTask.m_vDefaultAnimationCompositionData.clear();
}

ANGameResourcesData* ANGame::GetGameResourcesData()
{
	return this->m_pGameResourcesData;
}

ANEntityList* ANGame::GetEntityList()
{
	return this->m_pEntityList;
}

ANInteractionMessagesList* ANGame::GetInteractionList()
{
	return this->m_pInteractionMessagesList;
}
