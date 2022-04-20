#include "../../ANEngine.h"

ANScriptManager::ANScriptManager(ANCore* pCore, const char* pszMainScriptPath) :
	IANError(),
	m_pszMainScriptPath((char*)pszMainScriptPath),
	m_pCore(pCore)
{
	
}

ANScriptManager::~ANScriptManager()
{

}

bool ANScriptManager::InitScripts()
{
	auto& MainScript = this->m_mScripts[this->m_pszMainScriptPath] = ANMemory::GetInstance()->Allocate<ANScript>(this->m_pCore, this->m_pszMainScriptPath);

	if (!MainScript->InitializeScript())
	{
		this->SetError("%s() -> Main script init error\n%s", __FUNCTION__, MainScript->What());
		return false;
	}

	MainScript->Run();

	/*for (auto& s : this->m_mScripts)
	{
		if (s.first == this->m_pszMainScriptPath)
			continue;

		if (!s.second->InitializeScript())
		{
			printf("%s\n", s.second->What());
		}
	}*/
	
	return true;
}

bool ANScriptManager::AddScript(char* pszScriptPath)
{
	this->m_mScripts[pszScriptPath] = ANMemory::GetInstance()->Allocate<ANScript>(this->m_pCore, pszScriptPath);
	return true;
}
