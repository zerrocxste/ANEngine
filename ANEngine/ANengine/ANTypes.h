#pragma once

#define ARRSIZE(v) (sizeof(v) / sizeof(*v))

typedef std::size_t anSize;

typedef void* ANModuleHandle;
typedef void* ANWindowHandle;

struct ANWindowData
{
	char m_WindowTitle[256];
	bool m_bHasWindowFrame;
	anVec2 m_vWindowPosition;
	anVec2 m_vWindowSize;
};

typedef void* ANImageID;
typedef void* ANFontID;
typedef void* ANInternalGuiWindowID;
typedef void* ANGuiWindowID;
typedef __int64 ANPerfomanceTick;
//typedef void** ANAnimationComposition;

enum RGBA;

enum CursorKey;
struct KeyInformation;

enum FontAppierence;

struct ANWorldMetrics;
struct ANUniqueInteractionMesssage;

struct ANComponents
{
	ANInput* m_pANInput;
	ANRenderer* m_ANRenderer;
	ANGame* m_pANGame;
	ANResourceManager* m_pANResourceManager;
	ANApi* m_ANApi;
	ANGui* m_ANGui;
	ANPerfomance* m_ANPerfomance;
	ANPlatform* m_pANPlatform;
};

typedef struct 
{
	bool m_bIsUnique;
	ANImageID m_Frame;
} ANCompositionFrame, *pANCompositionFrame;

typedef pANCompositionFrame ANAnimationComposition;

using anFramesLength = short;
constexpr auto FRAMES_DATA_BYTE_LENGTH = sizeof(anFramesLength);