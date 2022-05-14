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
	float m_WorldZoom;
	ANImageID LevelBG;
	IANWorld* m_pWorld;
	IANEntity* m_pMainActor;
	ANGuiWindowID m_GuiWindow;
};