#pragma once

class ANScriptInterpriter : public IANError
{
public:
	ANScriptInterpriter(ANCore* pCore);
	~ANScriptInterpriter();

	void AddFunctionToList(const char* pszFunctionName, void* pToCallFunction);

	bool ProcessIncludes(char* pszScriptFile);
	bool ProcessFunction(char* pszScriptFile, const char* pszName);

	bool FindFunc(char* pszScriptFile, const char* pszName, char*& szLine);
private:
	ANCore* m_pCore;

	char* ReadArg(char* szLine);
	char* ReadStr(char* szLine);

	bool RunFunction(char* szFuncName, char* szArg);

	std::map<const char*, void*> m_mFunctionList;
};