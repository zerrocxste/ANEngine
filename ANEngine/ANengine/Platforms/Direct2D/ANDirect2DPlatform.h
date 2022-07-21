#pragma once

#ifdef BACKEND_DIRECT2D
#include <d2d1.h>
#pragma comment (lib, "d2d1.lib")

#include <dwrite.h>
#pragma comment (lib, "dwrite.lib")

#include <wincodec.h>
#pragma comment (lib, "windowscodecs.lib")

#define D2D_RENDER_FUNCTION

namespace renderBackend
{
	bool InitializeRenderer(ANWindowHandle WindowHandle, void* pReversed);
	ANRendererFuncionsTable* GetRendererFunctionsTable();
}
#endif // BACKEND_DIRECT2D