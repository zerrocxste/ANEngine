#include "../ANEngine.h"

ANCore::ANCore(
	RenderTypes RenderType, 
	const char* pszWindowName,
	anVec2 vWindowPosition, 
	anVec2 vWindowSize, 
	bool bHasWindowFrame) : m_bIsInitialized(false)
{
	m_EngineComponents.m_pANWindow = ANMemory::GetInstance()->Allocate<ANWindow>(this, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame);
	m_EngineComponents.m_pANInput = ANMemory::GetInstance()->Allocate<ANInput>(this);
	m_EngineComponents.m_ANRenderer = ANMemory::GetInstance()->Allocate<ANRenderer>(this, RenderType);
	m_EngineComponents.m_pANGame = ANMemory::GetInstance()->Allocate<ANGame>(this);
	m_EngineComponents.m_pANResourceManager = ANMemory::GetInstance()->Allocate<ANResourceManager>();
	m_EngineComponents.m_pANScene = ANMemory::GetInstance()->Allocate<ANScene>(this);
	m_EngineComponents.m_ANApi = ANMemory::GetInstance()->Allocate<ANApi>(this);
	m_EngineComponents.m_ANGui = ANMemory::GetInstance()->Allocate<ANGui>(this);
}

ANCore::~ANCore()
{

}

ANWindow* ANCore::GetWindow()
{
	assert(this->m_EngineComponents.m_pANWindow != nullptr);
	return this->m_EngineComponents.m_pANWindow;
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

ANScene* ANCore::GetScene()
{
	assert(this->m_EngineComponents.m_pANScene != nullptr);
	return this->m_EngineComponents.m_pANScene;
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

bool ANCore::Initialize()
{
	if (this->m_bIsInitialized)
		return true;

	auto w = this->GetWindow();

	if (!w->MakeWindow())
	{
		this->SetError("%s() -> Error make window\n%s", __FUNCTION__, w->What());
		return false;
	}

	auto r = this->GetRenderer();

	if (!r->Initalize())
	{
		this->SetError("%s() -> Error initialize renderer\n%s", __FUNCTION__, r->What());
		return false;
	}

	this->m_bIsInitialized = true;

	return true;
}

bool ANCore::Run()
{
	auto s = GetScene();

	if (!s->Run())
	{
		this->SetError("%s() -> Scene run error\n%s", __FUNCTION__, s->What());
		return false;
	}

	return true;
}