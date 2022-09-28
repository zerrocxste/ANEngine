#include "ANSDK.h"

IANLoader* ANEngine::CreateLoaderContext(
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame,
	bool bVerticalSync)
{
	static auto hANEngineModule = LoadLibrary("ANEngine.dll");

	if (!hANEngineModule)
	{
		return nullptr;
	}

	static auto pfCreateEngineInstance = (fCreateEngineInstance)GetProcAddress(hANEngineModule, "CreateEngineInstance");

	if (!pfCreateEngineInstance)
	{
		return nullptr;
	}

	return pfCreateEngineInstance(pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame, bVerticalSync);
}