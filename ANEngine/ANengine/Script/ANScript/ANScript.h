#pragma once

class ANScript : public IANError
{
public:
	ANScript(ANCore* pCore, const char* pszScriptPath);
	~ANScript();

	bool InitializeScript();
private:
	ANCore* m_pCore;

	const char* m_pszScriptPath;
	ANUniqueResource m_ScriptResource;

	bool FindFunc(ANUniqueResource* pScriptResource, const char* pszName, std::uint32_t* iLinePos);
};
