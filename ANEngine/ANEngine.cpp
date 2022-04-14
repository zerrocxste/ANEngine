#include <iostream>

#include "ANengine/ANEngine.h"

std::vector<HANDLE> vContextes;

void CreateEngine(void* Arg)
{
	auto pCtx = new ANCore(RenderTypes::D2D, "ANEngine", anVec2(100.f, 100.f), anVec2(500.f, 500.f), true);

	pCtx->Run();

	printf("End thread: %d\n", (int)Arg);
}

void CreateEngineCount(int c, std::vector<HANDLE>& vContextes, void* ThreadFunc)
{
	for (auto i = 0; i < c; i++)
	{
		vContextes.push_back(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)CreateEngine, (void*)i, 0, nullptr));
	}
}

void WaitThreadHandles(std::vector<HANDLE>& vContextes)
{
	for (auto h : vContextes)
	{
		WaitForSingleObject(h, INFINITE);
	}
}

int main()
{
	CreateEngineCount(5, vContextes, CreateEngine);

	WaitThreadHandles(vContextes);
}
