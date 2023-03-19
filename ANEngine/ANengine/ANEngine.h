#pragma once

constexpr auto VERSION = "1.b";

#define BACKEND_DIRECT2D

#include <Windows.h>
#include <assert.h>
#include <direct.h>

#include <intrin.h>

#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>

class ANCore;
class ANWindow;
class ANInput;
class ANRenderer;
class ANGame;
class ANResourceManager;
class ANApi;
class ANPerfomance;

#ifdef _WIN32
class ANPlatformWin32;
typedef ANPlatformWin32 ANPlatform;
#endif // _WIN32

class ANGui;
class ANGameResourcesData;
class ANEntity;
class ANEntityList;
class ANEntityGroup;
class ANAnimationCompositionController;

class IANApi;
class IANGameScene;
class IANWorld;
class IANEntity;
class IANEntityGroup;
class IANAnimationCompositionController;
class IANInteractionController;
class IANInteractionMessagesList;

#include "ANMath/ANVec2/ANVec2.h"
#include "ANMath/ANVec3/ANVec3.h"
#include "ANMath/ANRect/ANRect.h"
#include "ANMath/ANColor/ANColor.h"

#include "ANTypes.h"

#include "ANMath/ANMathUtils/ANMathUtils.h"

#include "ANInterfacePointer/ANInterfacePointer.h"

#include "Interfaces/Game/GameEntity/IANInteractionController/IANInteractionController.h"
#include "Interfaces/Game/IANInteractionMessagesList/IANInteractionMessagesList.h"
#include "Interfaces/Game/GameEntity/IANEntity/IANEntity.h"
#include "Interfaces/Game/GameEntity/IANEntityGroup/IANEntityGroup.h"
#include "Interfaces/Game/IANAnimationCompositionController/IANAnimationCompositionController.h"
#include "Interfaces/IANError/IANError.h"
#include "Interfaces/Game/IANWorld/IANWorld.h"
#include "Interfaces/IANGameScene/IANGameScene.h"
#include "Interfaces/GuiSkin/GuiSkin.h"
#include "Interfaces/IANApi/IANApi.h"
#include "Interfaces/IANLoader/IANLoader.h"
#include "Interfaces/IANRendererBackend/IANRendererBackend.h"

#include "ANMemory/ANMemory.h"

#if _WIN32
#include "Platforms/Win32/ANWin32Platform.h"
#ifdef BACKEND_DIRECT2D
#include "Platforms/Direct2D/ANDirect2DPlatform.h"
#endif
#endif

#include "ResourcesManager/ANUniqueResource/ANUniqueResource.h"
#include "ResourcesManager/ANResourceManager/ANResourceManager.h"
#include "ANPerfomance/ANPerfomance.h"
#include "ANRenderer/ANRenderer.h"
#include "ANInput/ANInput.h"
#include "ANWorld/ANWorld.h"
#include "ANGameResourcesData/ANGameResourcesData.h"
#include "GameEntity/ANEntityList/ANEntityList.h"
#include "GameEntity/ANInteractionMessagesList/ANInteractionMessagesList.h"
#include "GameEntity/ANEntity/ANEntity.h"
#include "GameEntity/ANEntityGroup/ANEntityGroup.h"
#include "GameEntity/ANAnimationCompositionController/ANAnimationCompositionController.h"
#include "ANGame/ANGame.h"
#include "ANApi/ANApi.h"
#include "Gui/ANGuiWindow/ANGuiWindow.h"
#include "Gui/ANGui/ANGui.h"
#include "ANCore/ANCore.h"
#include "ANLoader/ANLoader.h"