#include "ANEngine.h"

ANCore::ANCore(
	RenderTypes RenderType, 
	const char* pszWindowName,
	anVec2 vWindowPosition, 
	anVec2 vWindowSize, 
	bool bHasWindowFrame,
	const char* pszPathMainScriptEntry)
{
	m_EngineComponents.m_pANWindow = ANMemory::GetInstance()->Allocate<ANWindow>(this, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame);
	m_EngineComponents.m_pANInput = ANMemory::GetInstance()->Allocate<ANInput>(this);
	m_EngineComponents.m_ANRenderer = ANMemory::GetInstance()->Allocate<ANRenderer>(this, RenderType);
	m_EngineComponents.m_pANGame = ANMemory::GetInstance()->Allocate<ANGame>(this);
	m_EngineComponents.m_pANResourceManager = ANMemory::GetInstance()->Allocate<ANResourceManager>();
	m_EngineComponents.m_pANScriptManager = ANMemory::GetInstance()->Allocate<ANScriptManager>(this, pszPathMainScriptEntry);
	m_EngineComponents.m_pANScene = ANMemory::GetInstance()->Allocate<ANScene>(this);
	m_EngineComponents.m_pANScriptInterpriter = ANMemory::GetInstance()->Allocate<ANScriptInterpriter>(this);
}

ANCore::~ANCore()
{

}

bool ANCore::Initialize()
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

ANScriptManager* ANCore::GetScriptManager()
{
	assert(this->m_EngineComponents.m_pANScriptManager != nullptr);
	return this->m_EngineComponents.m_pANScriptManager;
}

ANScriptInterpriter* ANCore::GetScriptInterpreter()
{
	assert(this->m_EngineComponents.m_pANScriptInterpriter != nullptr);
	return this->m_EngineComponents.m_pANScriptInterpriter;
}

ANScene* ANCore::GetScene()
{
	assert(this->m_EngineComponents.m_pANScene != nullptr);
	return this->m_EngineComponents.m_pANScene;
}

void CreateImage(const char* pszImageName)
{

}

bool ANCore::Run()
{
	auto s = GetScene();

	if (!s->Run())
	{
		MessageBox(0, s->What(), "Remember, No Russian", MB_OK);
		return false;
	}

	return true;
}
