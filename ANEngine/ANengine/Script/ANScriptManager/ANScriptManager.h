#pragma once

class ANScriptManager : public IANError
{
public:
	ANScriptManager(ANCore* pCore, const char* pszMainScriptPath);
	~ANScriptManager();

	bool ProcessScripts();
private:
	ANCore* m_pCore;
	const char* m_pszMainScriptPath;
	std::map<const char*, ANScript*> m_mScripts;
};