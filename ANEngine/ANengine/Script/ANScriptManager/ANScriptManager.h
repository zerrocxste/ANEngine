#pragma once

class ANScriptManager : public IANError
{
public:
	ANScriptManager(ANCore* pCore, const char* pszMainScriptPath);
	~ANScriptManager();

	bool InitScripts();

	bool AddScript(char* pszScriptPath);
private:
	ANCore* m_pCore;
	char* m_pszMainScriptPath;
	std::map<const char*, ANScript*> m_mScripts;
	ANScript* m_pCurrentScriptContext;
};