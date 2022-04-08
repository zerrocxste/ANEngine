#include <iostream>

#include "ANengine/ANEngine.h"

int main()
{
	ANCore* pCtx = new ANCore();

	pCtx->Run();

	while (1)
	{
		Sleep(1);
	}
}
