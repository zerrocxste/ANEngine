#include "../ANEngine.h"

ANLoader::ANLoader(const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame,
	bool bVerticalSync)
{
	this->m_pInstance = new ANCore(pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame, bVerticalSync);
}

ANLoader::~ANLoader()
{
	DestroyContext();
}

bool ANLoader::InitializeLoader()
{
	if (!this->m_pInstance->Initialize())
	{
		this->SetError(__FUNCTION__ " > Initialize Loader error\n%s", this->m_pInstance->What());
		return false;
	}

	return true;
}

bool ANLoader::ConnectScene(IANGameScene* pGameScene)
{
	return this->m_pInstance->GetGame()->ConnectScene(pGameScene);
}

void ANLoader::RunScene()
{
	this->m_pInstance->Run();
}

bool ANLoader::DestroyContext()
{
	if (!this->m_pInstance)
		return false;

	delete this->m_pInstance;

	return true;
}
