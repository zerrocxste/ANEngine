#pragma once

class CTestLevel : public IANGameScene
{
public:
	CTestLevel();
	~CTestLevel();

	void OnLoadScene(IANApi* pApi) override;
	void OnUnloadScene(IANApi* pApi) override;
	void Entry(IANApi* pApi) override;

private:
	ANImageID LevelBG;

	ANGuiWindowID m_GuiWindow;
};