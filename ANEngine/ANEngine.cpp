#include <iostream>

#include "ANengine/ANEngine.h"

int main()
{
	auto pCtx = ANCore::CreateEngine();

	pCtx->Run();
}
