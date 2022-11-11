#include "includes.h"

#define FULLSCREEN 0

int main()
{
#if FULLSCREEN == 1
	anVec2 Pos = anVec2();
	anVec2 Size = anVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	bool HasWindowFrame = false;
#else
	anVec2 Pos = anVec2(10.f, 10.f);
	anVec2 Size = anVec2(984.f, 611.f);
	bool HasWindowFrame = true;
#endif // FULLSCREEN ==1

	auto pLoader = ANEngine::CreateLoaderContext("GameExample", Pos, Size, HasWindowFrame, true);

	if (!pLoader->InitializeLoader())
	{
		MessageBox(0, pLoader->What(), "Error", MB_ICONERROR);
		return 1;
	}

	pLoader->ConnectScene(new CTestLevel());

	pLoader->RunScene();

	return 0;
}