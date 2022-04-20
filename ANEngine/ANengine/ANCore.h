#pragma once

class ANCore
{
public:
	ANCore(RenderTypes RenderType,
		const char* pszWindowName,
		anVec2 vWindowPosition,
		anVec2 vWindowSize,
		bool bHasWindowFrame,
		const char* pszPathMainScriptEntry);

	~ANCore();

	bool Initialize();

	ANWindow* GetWindow();
	ANInput* GetInput();
	ANRenderer* GetRenderer();
	ANGame* GetGame();
	ANResourceManager* GetResourceManager();
	ANScriptManager* GetScriptManager();
	ANScriptInterpriter* GetScriptInterpreter();
	ANScene* GetScene();

	bool Run();
private:
	ANComponents m_EngineComponents;
};

