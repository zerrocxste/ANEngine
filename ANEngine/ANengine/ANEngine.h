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

class ANCore;
class ANWindow;
class ANInput;
class ANRenderer;
class ANGame;
class ANResourceManager;
class ANScene;
class ANApi;
class ANGui;

#include "ANTypes.h"

#include "Interfaces/IANError/IANError.h"
#include "Interfaces/IANApi/IANApi.h"
#include "Interfaces/IANGameScene/IANGameScene.h"
#include "Interfaces/IANLoader/IANLoader.h"

#include "ANMemory/ANMemory.h"

#include "ResourcesManager/ANUniqueResource/ANUniqueResource.h"
#include "ResourcesManager/ANResourceManager/ANResourceManager.h"
#include "ANRenderer/ANRenderer.h"
#include "ANInput/ANInput.h"
#include "ANWindow/ANWindow.h"
#include "ANGame/ANGame.h"
#include "ANScene/ANScene.h"
#include "ANApi/ANApi.h"
#include "ANGui/ANGui.h"
#include "ANCore/ANCore.h"
#include "ANLoader/ANLoader.h"