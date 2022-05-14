#include "ANSDK.h"

IANLoader* CreateEngineInstance(
	RenderTypes RenderType,
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

	return pfCreateEngineInstance(RenderType, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame, bVerticalSync);
}