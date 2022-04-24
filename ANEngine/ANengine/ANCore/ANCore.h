#pragma once

class ANCore : public IANError
{
public:
	ANCore(RenderTypes RenderType,
		const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame);

	~ANCore();

	ANWindow* GetWindow();
	ANInput* GetInput();
	ANRenderer* GetRenderer();
	ANGame* GetGame();
	ANResourceManager* GetResourceManager();
	ANScene* GetScene();
	ANApi* GetApi();
	ANGui* GetGui();

	bool Initialize();
	bool Run();
private:
	ANComponents m_EngineComponents;

	bool m_bIsInitialized;
};

