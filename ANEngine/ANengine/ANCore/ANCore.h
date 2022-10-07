#pragma once

class ANCore : public IANError
{
public:
	ANCore(const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame, 
		bool bVerticalSync);

	~ANCore();

	ANInput* GetInput();
	ANRenderer* GetRenderer();
	ANGame* GetGame();
	ANResourceManager* GetResourceManager();
	ANApi* GetApi();
	ANGui* GetGui();
	ANPerfomance* GetPerfomance();
	ANPlatform* GetPlatform();

	bool Initialize();
	bool Run();

	const char* GetVersion();
private:
	ANComponents m_EngineComponents;

	bool m_bIsInitialized;
};

