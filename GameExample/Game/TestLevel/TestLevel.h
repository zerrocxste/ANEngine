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

	IANWorld* m_pWorld;
	ANImageID LevelBG;

	IANEntity* m_pMainActor;
	ANAnimationComposition m_WoodyComposition;
	ANAnimationComposition m_WoodyCompositionLeft;
	ANAnimationComposition m_WoodyCompositionRight;

	IANEntity* m_pDoorEntity;
	ANAnimationComposition m_DoorComposition;
};