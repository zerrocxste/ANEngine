#pragma once

struct ANComponents
{
	ANWindow* m_pANWindow;
	ANInput* m_pANInput;
	ANRenderer* m_ANRenderer;
	ANGame* m_pANGame;
	ANResourceManager* m_pANResourceManager;
};

class ANCore
{
public:
	ANCore(RenderTypes RenderType,
		const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame);
	~ANCore();

	bool Initialize();

	ANWindow* GetWindow();
	ANInput* GetInput();
	ANRenderer* GetRenderer();
	ANGame* GetGame();
	ANResourceManager* GetResourceManager();

	bool Run();
private:
	ANComponents m_EngineComponents;
};

