#pragma once

class ANCore : public IANError
{
public:
	ANCore(RenderTypes RenderType,
		const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame, 
		bool bVerticalSync);

	~ANCore();

	ANWindow* GetWindow();
	ANInput* GetInput();
	ANRenderer* GetRenderer();
	ANGame* GetGame();
	ANResourceManager* GetResourceManager();
	ANApi* GetApi();
	ANGui* GetGui();
	ANPerfomance* GetPerfomance();

	bool Initialize();
	bool Run();
private:
	ANComponents m_EngineComponents;

	bool m_bIsInitialized;
};

