#include "../../ANEngine.h"

ANScript::ANScript(ANCore* pCore, const char* pszScriptPath) :
	IANError(),
	m_pCore(pCore),
	m_pszScriptPath(pszScriptPath)
{
	memset(&this->m_ScriptResource, 0 , sizeof(decltype(this->m_ScriptResource)));
}

ANScript::~ANScript()
{

}

bool ANScript::InitializeScript()
{
	if (!this->m_pCore->GetResourceManager()->ReadTextFile(this->m_pszScriptPath, &this->m_ScriptResource))
	{
		this->SetError("%s() -> File '%s' load error\n%s", __FUNCTION__, this->m_pszScriptPath, this->m_pCore->GetResourceManager()->What());
		return false;
	}

	printf("\nSCRIPT '%s' /////////////////////////////////////\n\n%s\n\n/////////////////////////////////////\n", this->m_pszScriptPath, this->m_ScriptResource.GetResourceLocation());

	return true;
}

bool ANScript::FindFunc(ANUniqueResource* pScriptResource, const char* pszName, std::uint32_t* iLinePos)
{
	return false;
}
