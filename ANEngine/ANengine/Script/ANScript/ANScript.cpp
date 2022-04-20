#include "../../ANEngine.h"

ANScript::ANScript(ANCore* pCore, char* szScriptPath) :
	IANError(),
	m_pCore(pCore)
{
	strncpy(m_szScriptPath, szScriptPath, strlen(szScriptPath));
	memset(&this->m_ScriptResource, 0 , sizeof(ANUniqueResource));
}

ANScript::~ANScript()
{

}

bool ANScript::InitializeScript()
{
	if (!this->m_pCore->GetResourceManager()->ReadTextFile(this->m_szScriptPath, &this->m_ScriptResource))
	{
		this->SetError("%s() -> File '%s' load error\n%s", __FUNCTION__, this->m_szScriptPath, this->m_pCore->GetResourceManager()->What());
		return false;
	}

	//printf("\nSCRIPT '%s' /////////////////////////////////////\n\n%s\n\n/////////////////////////////////////\n\n", this->m_szScriptPath, GetScriptFile());

	if (!this->m_pCore->GetScriptInterpreter()->ProcessIncludes(GetScriptFile()))
	{
		printf("%s() -> '%s' Not include another files\n", __FUNCTION__, this->m_szScriptPath);
		return false;
	}

	if (!this->m_pCore->GetScriptInterpreter()->ProcessFunction(GetScriptFile(), "load_resource"))
	{
		printf("%s() -> '%s' Error call\n", __FUNCTION__, this->m_szScriptPath);
		return false;
	}

	return true;
}

bool ANScript::Run()
{


	return true;
}

char* ANScript::GetScriptFile()
{
	return (char*)this->m_ScriptResource.GetResourceLocation();
}