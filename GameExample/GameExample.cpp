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

	auto Loader = CreateEngineInstance(RenderTypes::D2D, "GameExample", Pos, Size, HasWindowFrame);

	if (!Loader->InitializeLoader())
	{
		MessageBox(0, Loader->What(), "Error", MB_ICONERROR);
		return 1;
	}

	Loader->ConnectScene(new CTestGameScene());

	if (!Loader->RunScene())
	{
		MessageBox(0, Loader->What(), "Error", MB_ICONERROR);
		return 1;
	}

	return 0;
}