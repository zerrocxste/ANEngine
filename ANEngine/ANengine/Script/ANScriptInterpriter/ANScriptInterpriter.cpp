#include "../../ANEngine.h"

ANScriptInterpriter::ANScriptInterpriter(ANCore* pCore) : 
	IANError(), 
	m_pCore(pCore)
{

}

ANScriptInterpriter::~ANScriptInterpriter()
{

}

void ANScriptInterpriter::AddFunctionToList(const char* pszFunctionName, void* pToCallFunction)
{
	this->m_mFunctionList[pszFunctionName] = pToCallFunction;
}

bool ANScriptInterpriter::ProcessIncludes(char* pszScriptFile)
{
	auto ret = false;

	auto Line = pszScriptFile;

	while (auto IsFound = strstr(Line, UseDerective))
	{
		ret = true;

		auto Str = ReadStr(IsFound);

		if (!Str)
			continue;

		printf("Additional script: %s\n", Str);

		Line = IsFound + strlen(UseDerective);

		//this->m_pCore->GetScriptManager()->AddScript(Str);
	}

	return ret;
}

bool ANScriptInterpriter::ProcessFunction(char* pszScriptFile, const char* pszName)
{
	char szFunctionName[256] = { 0 };
	char szFunctionArg[256] = { 0 };

	auto szSearch = (char*)strstr(pszScriptFile, pszName);

	if (!szSearch)
	{
		this->SetError("%s() -> Function '%s' not found", __FUNCTION__, pszName);
		return false;
	}

	bool bBeginFuncParsed = false;

	while (true)
	{
		if (!bBeginFuncParsed && *(szSearch - 1) != '{')
		{
			szSearch++;
			continue;
		}
		else
			bBeginFuncParsed = true;

		auto Sym = *szSearch;

		if (!Sym || Sym == '}')
			break;

		if (Sym == '\x09' || Sym == ' ') //TAB \ SPACE
		{
			szSearch += 1;
			continue;
		}

		if (Sym == '\x0D' && szSearch[1] == '\x0A') //NEW LINE (2 BYTES)
		{
			szSearch += 2;
			continue;
		}

		for (auto i = 0; *szSearch != '(' && i < sizeof(szFunctionName); i++, szSearch++)
		{
			if (*szSearch == ')')
			{
				this->SetError("%s() -> Bad syntax, Line: %d. Call closure cannot be without initial parenthesis", __FUNCTION__, szSearch - pszScriptFile);
				break;
			}

			if (*szSearch == ';')
			{
				this->SetError("%s() -> Bad syntax, Line: %d. Call cannot be without arguments", __FUNCTION__, szSearch - pszScriptFile);
				break;
			}

			szFunctionName[i] = *szSearch;
		}	

		auto FoundEndCall = false;

		for (auto i = 0; i < sizeof(szFunctionName); i++, szSearch++)
		{
			if (*szSearch == ';')
			{
				FoundEndCall = true;
				break;
			}

			szFunctionArg[i] = *szSearch;
		}

		if (!FoundEndCall)
		{
			this->SetError("%s() -> Semicolon required, Line: %d", __FUNCTION__, szSearch - pszScriptFile);
			return false;
		}
			
		printf("%s | %s\n", szFunctionName, szFunctionArg);

		RunFunction(szFunctionName, szFunctionArg);

		break;
	}

	return true;
}

bool ANScriptInterpriter::FindFunc(char* pszScriptFile, const char* pszName, char*& szLine)
{
	auto IsFound = strstr(pszScriptFile, pszName);

	if (IsFound)
	{
		IsFound -= 1;

		while (*IsFound == ' ')
			IsFound--;

		IsFound -= 3;

		szLine = IsFound;

		return true;
	}

	return false;
}

char* ANScriptInterpriter::ReadArg(char* szLine)
{

}

char* ANScriptInterpriter::ReadStr(char* szLine)
{
	while (*szLine != '"')
		szLine++;

	char szBuf[1024] = { 0 };

	for (auto i = 0; i < sizeof(szBuf); i++)
	{
		if (szLine[i] == 0)
			continue;

		if (szLine[i] == ' ')
			continue;

		if (szLine[i] == '"')
			continue;

		auto Break = false;

		for (auto j = 0; j < sizeof(szBuf); j++)
		{
			auto Sym = szLine[i + j];

			if (Sym == '"')
			{
				Break = true;
				break;
			}

			szBuf[j] = szLine[i + j];
		}

		if (Break)
			break;
	}

	if (!*szBuf)
	{
		this->SetError("%s() -> Bad string", __FUNCTION__);
		return nullptr;
	}	

	return szBuf;
}

bool ANScriptInterpriter::RunFunction(char* szFuncName, char* szArg)
{
	if (!szFuncName || !szArg)
	{
		this->SetError("%s() -> Invalid parameters", __FUNCTION__);
		return false;
	}

	if (!strcmp(szFuncName, "load_image"))
	{
		ANImageID ImageID;
		ANUniqueResource Image;

		std::string Arg = ReadStr(szArg);

		if (!this->m_pCore->GetResourceManager()->ReadBinFile(Arg.c_str(), &Image))
		{
			printf("%s\n", this->m_pCore->GetResourceManager()->What());
			return false;
		}

		if (!this->m_pCore->GetRenderer()->CreateImageFromResource(&Image, &ImageID))
		{
			printf("%s\n", this->m_pCore->GetRenderer()->What());
			return false;
		}

		return true;
	}
	if (!strcmp(szFuncName, "draw_image"))
	{
		//this->m_pCore->GetRenderer()->DrawImage();
	}

	return false;
}

