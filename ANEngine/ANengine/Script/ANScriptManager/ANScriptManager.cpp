#include "../../ANEngine.h"

ANScriptManager::ANScriptManager(ANCore* pCore, const char* pszMainScriptPath) :
	IANError(),
	m_pszMainScriptPath(pszMainScriptPath),
	m_pCore(pCore)
{
	
}

ANScriptManager::~ANScriptManager()
{

}

bool ANScriptManager::ProcessScripts()
{
	auto& MainScript = this->m_mScripts[this->m_pszMainScriptPath] = ANMemory::GetInstance()->Allocate<ANScript>(this->m_pCore, this->m_pszMainScriptPath);

	if (!MainScript->InitializeScript())
	{
		this->SetError("%s() -> Main script init error\n%s", __FUNCTION__, MainScript->What());
		return false;
	}
	
	return true;
}
