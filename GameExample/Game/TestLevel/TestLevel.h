#pragma once

class DoorEntityInteractionController : public IANInteractionController
{
public:
	bool ActionHandler(IANApi* pApi, const char* pszEventClassID, const char* pszEventMessage, IANEntity* pThisEntity, IANEntity** pRemoteEntity, void* pReversedUserData) override;
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

	void ClearDoorInteractions(IANApi* pApi);
private:
	float m_WorldZoom;

	IANWorld* m_pWorld;
	ANAnimationComposition m_WorldComposition;

	IANEntity* m_pMainActor;
	ANAnimationComposition m_WoodyComposition;
	ANAnimationComposition m_WoodyCompositionLeft;
	ANAnimationComposition m_WoodyCompositionRight;
	ANAnimationComposition m_WoodyDoorLeave;
	ANAnimationComposition m_WoodyDoorEnter;

	IANEntity* m_pDoorEntityHallwayKitchen;
	IANEntity* m_pDoorEntityKitchenHallway;

	IANEntity* m_pDoorEntityHallwayHall;
	IANEntity* m_pDoorEntityHallHallway;
	ANAnimationComposition m_DoorComposition;

	IANEntity* MovePoint;
};