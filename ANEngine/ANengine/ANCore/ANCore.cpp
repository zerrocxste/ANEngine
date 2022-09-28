#include "../ANEngine.h"

ANCore::ANCore(
	const char* pszWindowName,
	anVec2 vWindowPosition, 
	anVec2 vWindowSize, 
	bool bHasWindowFrame,
	bool bVerticalSync) : m_bIsInitialized(false)
{
	m_EngineComponents.m_pANInput = ANMemory::GetInstance()->Allocate<ANInput>(this);
	m_EngineComponents.m_ANRenderer = ANMemory::GetInstance()->Allocate<ANRenderer>(this, bVerticalSync);
	m_EngineComponents.m_pANGame = ANMemory::GetInstance()->Allocate<ANGame>(this);
	m_EngineComponents.m_pANResourceManager = ANMemory::GetInstance()->Allocate<ANResourceManager>();
	m_EngineComponents.m_ANApi = ANMemory::GetInstance()->Allocate<ANApi>(this);
	m_EngineComponents.m_ANGui = ANMemory::GetInstance()->Allocate<ANGui>(this);
	m_EngineComponents.m_ANPerfomance = ANMemory::GetInstance()->Allocate<ANPerfomance>();
	m_EngineComponents.m_pANPlatform = ANMemory::GetInstance()->Allocate<ANPlatform>(this, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame);
}

ANCore::~ANCore()
{

}

ANInput* ANCore::GetInput()
{
	assert(this->m_EngineComponents.m_pANInput != nullptr);
	return this->m_EngineComponents.m_pANInput;
}

ANRenderer* ANCore::GetRenderer()
{
	assert(this->m_EngineComponents.m_ANRenderer != nullptr);
	return this->m_EngineComponents.m_ANRenderer;
}

ANGame* ANCore::GetGame()
{
	assert(this->m_EngineComponents.m_pANGame != nullptr);
	return this->m_EngineComponents.m_pANGame;
}

ANResourceManager* ANCore::GetResourceManager()
{
	assert(this->m_EngineComponents.m_pANResourceManager != nullptr);
	return this->m_EngineComponents.m_pANResourceManager;
}

ANApi* ANCore::GetApi()
{
	assert(this->m_EngineComponents.m_ANApi != nullptr);
	return this->m_EngineComponents.m_ANApi;
}

ANGui* ANCore::GetGui()
{
	assert(this->m_EngineComponents.m_ANGui != nullptr);
	return this->m_EngineComponents.m_ANGui;
}

ANPerfomance* ANCore::GetPerfomance()
{
	assert(this->m_EngineComponents.m_ANPerfomance != nullptr);
	return this->m_EngineComponents.m_ANPerfomance;
}

ANPlatform* ANCore::GetPlatform()
{
	assert(this->m_EngineComponents.m_pANPlatform != nullptr);
	return this->m_EngineComponents.m_pANPlatform;
}

bool ANCore::Initialize()
{
	if (this->m_bIsInitialized)
		return true;

	auto plt = this->GetPlatform();

	if (!plt->WindowCreate())
	{
		this->SetError(__FUNCTION__ " > Error make window\n%s", plt->What());
		return false;
	}

	auto r = this->GetRenderer();

	if (!r->Initalize())
	{
		this->SetError(__FUNCTION__ " > Error initialize renderer\n%s", r->What());
		return false;
	}

	this->m_bIsInitialized = true;

	return true;
}

bool ANCore::Run()
{
	auto plt = this->GetPlatform();
	auto r = this->GetRenderer();
	auto g = this->GetGame();
	auto i = this->GetInput();
	auto p = this->GetPerfomance();

	plt->WindowShow();

	while (!plt->ProcessWindow())
	{
		p->Update();

		r->BeginFrame();

		r->ClearScene();

		i->Update();

		if (!g->RunScene())
			break;

		r->EndFrame();
	}

	return true;
}
