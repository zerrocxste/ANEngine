#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <assert.h>
#include <fstream>
#include <direct.h>
#include <thread>

#include "ANMath/ANVec2/ANVec2.h"
#include "ANMath/ANVec3/ANVec3.h"
#include "ANMath/ANRect/ANRect.h"
#include "ANMath/ANColor/ANColor.h"

#include "ANMath/ANMathUtils/ANMathUtils.h"

class ANCore;
class ANWindow;
class ANInput;
class ANRenderer;
class ANGame;
class ANResourceManager;
class ANApi;
class ANGui;
class ANPerfomance;
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

#include "ANTypes.h"

#include "ANPointer/ANPointer.h"

#include "Interfaces/Game/GameEntity/Components/IANBasicEntity/IANBasicEntity.h"
#include "Interfaces/Game/GameEntity/Components/IANMovementController/IANMovementController.h"
#include "Interfaces/Game/GameEntity/Components/IANActionController/IANActionController.h"
#include "Interfaces/Game/GameEntity/Components/IANAnimationController/IANAnimationController.h"
#include "Interfaces/Game/GameEntity/IANEntity/IANEntity.h"
#include "Interfaces/Game/GameEntity/IANEntityGroup/IANEntityGroup.h"
#include "Interfaces/Game/IANAnimationCompositionController/IANAnimationCompositionController.h"
#include "Interfaces/IANError/IANError.h"
#include "Interfaces/Game/World/IANWorld.h"
#include "Interfaces/IANGameScene/IANGameScene.h"
#include "Interfaces/GuiSkin/GuiSkin.h"
#include "Interfaces/IANApi/IANApi.h"
#include "Interfaces/IANLoader/IANLoader.h"

#include "ANMemory/ANMemory.h"

#include "ResourcesManager/ANUniqueResource/ANUniqueResource.h"
#include "ResourcesManager/ANResourceManager/ANResourceManager.h"
#include "ANPerfomance/ANPerfomance.h"
#include "ANRenderer/ANRenderer.h"
#include "ANInput/ANInput.h"
#include "ANWindow/ANWindow.h"
#include "ANWorld/ANWorld.h"
#include "GameEntity/ANEntityList/ANEntityList.h"
#include "GameEntity/ANEntity/ANEntity.h"
#include "GameEntity/ANEntityGroup/ANEntityGroup.h"
#include "GameEntity/ANAnimationCompositionController/ANAnimationCompositionController.h"
#include "ANGame/ANGame.h"
#include "ANApi/ANApi.h"
#include "Gui/ANGuiWindow/ANGuiWindow.h"
#include "Gui/ANGui/ANGui.h"
#include "ANCore/ANCore.h"
#include "ANLoader/ANLoader.h"