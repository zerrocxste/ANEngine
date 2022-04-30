#include "includes.h"

int main()
{
	auto Loader = CreateEngineInstance(RenderTypes::D2D, "GameExample", anVec2(100.f, 100.f), anVec2(700.f, 700.f), true);

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