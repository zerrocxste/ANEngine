#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <fstream>
#include <direct.h>

#include <d2d1.h>
#pragma comment (lib, "d2d1.lib")

//#include <dwrite.h>
//#pragma comment (lib, "dwrite.lib")
//
//#include <wincodec.h>
//#pragma comment (lib, "windowscodecs.lib")

#include "Interfaces/ANError/ANError.h"

#include "ANMemory/ANMemory.h"

#include "ANMath/ANVec2/ANVec2.h"
#include "ANMath/ANVec3/ANVec3.h"
#include "ANMath/ANRect/ANRect.h"
#include "ANMath/ANColor/ANColor.h"

#include "ANTypes.h"

class ANCore;
class ANResourceManager;

#include "ResourcesManager/ANUniqueResource/ANUniqueResource.h"
#include "ResourcesManager/ANResourceManager/ANResourceManager.h"
#include "ANRenderer/ANRenderer.h"
#include "ANRenderer/ANRenderer.h"
#include "ANInput/ANInput.h"
#include "ANWindow/ANWindow.h"
#include "ANGame/ANGame.h"

#include "ANCore.h"


