#pragma once

class DoorEntityInteractionController : public IANInteractionController
{
private:
	bool m_bNextDoor;
public:
	DoorEntityInteractionController();

	bool ActionHandler(IANApi* pApi, 
		const char* pszEventClassID, 
		const char* pszEventMessage, 
		IANEntity* pThisEntity, 
		IANEntity** pRemoteEntity, 
		void* pReversedUserData, 
		bool bNeedCancelEvent) override;
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
	ANAnimationComposition m_WoodyDoorEnter;

	IANEntity* m_pDoorEntityHallwayKitchen;
	IANEntity* m_pDoorEntityKitchenHallway;

	IANEntity* m_pDoorEntityHallwayHall;
	IANEntity* m_pDoorEntityHallHallway;
	ANAnimationComposition m_DoorComposition;

	void ProcessDoorInteraction(IANApi* pApi, IANEntity*& ppEntity, const char* pszEventName);

	void CreateDoorEntity(IANApi* pApi, IANEntity*& ppEntity, const char* pszDoorName, anVec2 Origin);
};