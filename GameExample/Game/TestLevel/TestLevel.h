#pragma once

class DoorEntityInteractionController : public IANInteractionController
{
	bool ActionHandler(IANApi* pApi, const char* pszEventClassID, const char* pszEventMessage, IANEntity* pThisEntity, IANEntity* pRemoteEntity, void* pReversedUserData) override;
};

class CTestLevel : public IANGameScene
{
	friend DoorEntityInteractionController;
public:
	CTestLevel();
	~CTestLevel();

	void OnLoadScene(IANApi* pApi) override;
	void OnUnloadScene(IANApi* pApi) override;
	void Entry(IANApi* pApi) override;

private:
	float m_WorldZoom;

	IANWorld* m_pWorld;
	ANAnimationComposition m_WorldComposition;

	IANEntity* m_pMainActor;
	ANAnimationComposition m_WoodyComposition;
	ANAnimationComposition m_WoodyCompositionLeft;
	ANAnimationComposition m_WoodyCompositionRight;
	ANAnimationComposition m_WoodyDoorLeave;

	IANEntity* m_pDoorEntityHallwayKitchen;
	IANEntity* m_pDoorEntityHallwayHall;
	ANAnimationComposition m_DoorComposition;
};