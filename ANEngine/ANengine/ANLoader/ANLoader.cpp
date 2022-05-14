#include "../ANEngine.h"

ANLoader::ANLoader(RenderTypes RenderType,
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame,
	bool bVerticalSync)
{
	this->m_pInstance = new ANCore(RenderType, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame, bVerticalSync);
}

ANLoader::~ANLoader()
{
	DestroyContext();
}

bool ANLoader::InitializeLoader()
{
	if (!this->m_pInstance->Initialize())
	{
		this->SetError("%s() -> Initialize Loader error\n%s", __FUNCTION__, this->m_pInstance->What());
		return false;
	}

	return true;
}

bool ANLoader::ConnectScene(IANGameScene* pGameScene)
{
	return this->m_pInstance->GetGame()->ConnectScene(pGameScene);
}

bool ANLoader::RunScene()
{
	return this->m_pInstance->Run();
}

bool ANLoader::DestroyContext()
{
	if (!this->m_pInstance)
		return false;

	delete this->m_pInstance;

	return true;
}
