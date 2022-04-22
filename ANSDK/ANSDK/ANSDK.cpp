#include "ANSDK.h"

IANLoader* CreateEngineInstance(
	RenderTypes RenderType,
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame)
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

	return pfCreateEngineInstance(RenderType, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame);
}

int main()
{
	return 0;
}