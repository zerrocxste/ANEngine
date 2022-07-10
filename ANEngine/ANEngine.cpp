#include "ANengine/ANEngine.h"

constexpr auto MODULE_DESC = "AlterNative engine (ANEngine) Engine module. Timestamp: " __DATE__;

extern "C" __declspec(dllexport) IANLoader * __stdcall CreateEngineInstance(
	RenderTypes RenderType,
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame,
	bool bVerticalSync)
{
	return new ANLoader(RenderType, pszWindowName, vWindowPosition, vWindowSize, bHasWindowFrame, bVerticalSync);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf("[+] " __FUNCTION__ " > %s\n", MODULE_DESC);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


