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
	ANCore();
	~ANCore();

	ANWindow* GetWindow();
	ANInput* GetInput();
	ANRenderer* GetRenderer();
	ANGame* GetGame();
	ANResourceManager* GetResourceManager();

	bool Run();

	static ANCore* CreateEngine();
private:
	ANComponents m_EngineComponents;
};

