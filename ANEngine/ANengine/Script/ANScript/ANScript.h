#pragma once

class ANScript : public IANError
{
public:
	ANScript(ANCore* pCore, char* pszScriptPath);
	~ANScript();

	bool InitializeScript();

	bool Run();
private:
	ANCore* m_pCore;

	char m_szScriptPath[255];
	ANUniqueResource m_ScriptResource;

	char* GetScriptFile();
};
