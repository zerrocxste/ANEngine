#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#include "ANMath/ANVec2/ANVec2.h"
#include "ANMath/ANVec3/ANVec3.h"
#include "ANMath/ANRect/ANRect.h"
#include "ANMath/ANColor/ANColor.h"

typedef void* ANImageID;
typedef void* ANFontID;
typedef void* ANGuiWindowID;
typedef __int64 ANPerfomanceTick;
typedef void** ANAnimationComposition;

class IANApi;
class IANGameScene;
class IANWorld;
class IANEntity;
class IANEntityGroup;
class IANAnimationCompositionController;

#include "ANPointer/ANPointer.h"
#include "IANAnimationCompositionController/IANAnimationCompositionController.h"
#include "GameEntity/Components/IANBasicEntity/IANBasicEntity.h"
#include "GameEntity/Components/IANMovementController/IANMovementController.h"
#include "GameEntity/Components/IANActionController/IANActionController.h"
#include "GameEntity/Components/IANAnimationController/IANAnimationController.h"
#include "GameEntity/IANEntity/IANEntity.h"
#include "GameEntity/IANEntityGroup/IANEntityGroup.h"
#include "IANWorld/IANWorld.h"
#include "IANError/IANError.h"
#include "IANGameScene/IANGameScene.h"
#include "Gui/GuiSkin.h"
#include "IANApi/IANApi.h"
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
	bool bHasWindowFrame,
	bool bVerticalSync);

IANLoader* CreateEngineInstance(
	RenderTypes RenderType,
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame,
	bool bVerticalSync);