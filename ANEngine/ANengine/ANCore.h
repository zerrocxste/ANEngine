#pragma once

struct ANComponents
{
	ANWindow* m_pANWindow;
	ANInput* m_pANInput;
	ANRenderer* m_ANRenderer;
	ANGame* m_pANGame;
	ANResourceManager* m_pANResourceManager;
	ANScriptManager* m_pANScriptManager;
	ANScriptInterpreter* m_pANScriptInterpreter;
};

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
	ANScriptInterpreter* GetScriptInterpreter();

	bool Run();
private:
	ANComponents m_EngineComponents;
};

