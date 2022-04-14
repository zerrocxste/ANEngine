#include <iostream>

#include "ANengine/ANEngine.h"

int main()
{
	auto pCtx = ANCore::GetInstance();

	pCtx->Run();
}
