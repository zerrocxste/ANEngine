#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <assert.h>
#include <fstream>
#include <direct.h>
#include <thread>

#include "Interfaces/ANError/ANError.h"

#include "ANMemory/ANMemory.h"

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
class ANScriptInterpriter;
class ANScript;
class ANScriptManager;
class ANScene;

#include "ANTypes.h"

#include "ResourcesManager/ANUniqueResource/ANUniqueResource.h"
#include "ResourcesManager/ANResourceManager/ANResourceManager.h"
#include "ANRenderer/ANRenderer.h"
#include "ANInput/ANInput.h"
#include "ANWindow/ANWindow.h"
#include "Script/ANScriptInterpriter/ANScriptInterpriter.h"
#include "Script/ANScript/ANScript.h"
#include "Script/ANScriptManager/ANScriptManager.h"
#include "Game/ANGame/ANGame.h"
#include "ANScene/ANScene.h"

#include "ANCore.h"


