#pragma once

#include <Windows.h>
#include <iostream>

#include "ANMath/ANVec2/ANVec2.h"
#include "ANMath/ANVec3/ANVec3.h"
#include "ANMath/ANRect/ANRect.h"
#include "ANMath/ANColor/ANColor.h"

typedef void* ANImageID;
typedef void* ANFontID;

#include "IANError/IANError.h"
#include "IANApi/IANApi.h"
#include "IANGameScene/IANGameScene.h"
#include "IANLoader/IANLoader.h"

enum RenderTypes
{
	D2D,
	D3D9,
	OPENGL
};

enum RGBA
{
	RED,
	GREEN,
	BLUE,
	ALPHA,
	RGBA_MAX_SIZE
};

using fCreateEngineInstance = IANLoader * (__stdcall*)(
	RenderTypes RenderType,
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame);

IANLoader* CreateEngineInstance(
	RenderTypes RenderType,
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame);