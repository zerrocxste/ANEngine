#pragma once

#define NDEBUG

#include <Windows.h>
#include <iostream>
#include <vector>
#include <deque>
#include <assert.h>

#include "ANMath/ANVec2/ANVec2.h"
#include "ANMath/ANVec3/ANVec3.h"
#include "ANMath/ANRect/ANRect.h"
#include "ANMath/ANColor/ANColor.h"

typedef std::size_t anSize;

struct ANWorldMetrics;

struct ANUniqueInteractionMesssage;

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
class IANInteractionController;
class IANInteractionMessagesList;

enum FontAppierence
{
	FONT_NONE = 0,
	FONT_SHADOW = 1 << 0,
};

#include "ANInterfacePointer/ANInterfacePointer.h"
#include "IANAnimationCompositionController/IANAnimationCompositionController.h"
#include "GameEntity/IANInteractionController/IANInteractionController.h"
#include "GameEntity/IANInteractionMessagesList/IANInteractionMessagesList.h"
#include "GameEntity/IANEntity/IANEntity.h"
#include "GameEntity/IANEntityGroup/IANEntityGroup.h"
#include "IANWorld/IANWorld.h"
#include "IANError/IANError.h"
#include "IANGameScene/IANGameScene.h"
#include "Gui/GuiSkin.h"
#include "IANApi/IANApi.h"
#include "IANLoader/IANLoader.h"

enum RGBA
{
	RED,
	GREEN,
	BLUE,
	ALPHA,
	RGBA_MAX_SIZE
};

enum CursorKey
{
	MAIN_FIRST,
	MAIN_SECOND,
	SECONDARY, 
	ADDITIONAL_1,
	ADDITIONAL_2
};

using fCreateEngineInstance = IANLoader * (__stdcall*)(
	const char* pszWindowName,
	anVec2 vWindowPosition,
	anVec2 vWindowSize,
	bool bHasWindowFrame,
	bool bVerticalSync);

namespace ANEngine
{
	IANLoader* CreateLoaderContext(
		const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame,
		bool bVerticalSync);
}