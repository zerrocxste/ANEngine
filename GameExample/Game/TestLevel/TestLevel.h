#pragma once

class DoorEntityInteractionController;
class CTestLevel;

class DoorEntityInteractionController : public IANInteractionController
{
private:

public:
	DoorEntityInteractionController();

	bool ActionHandler(IANApi* pApi, 
		const char* pszEventClassID, 
		const char* pszEventMessage, 
		IANEntity* pThisEntity, 
		IANEntity** pRemoteEntity, 
		void* pReversedUserData, 
		bool bNeedCancelEvent) override;

	void ResetDoorState(IANEntity* pThisEntity, IANEntity* pDestEntity, IANEntity* pActorEntity);
};

enum HOUSE_ROOM
{
	ROOM_EMPTY,
	HALLWAY,
	BATHROOM,
	KITCHEN,
	HALL
};

enum DOOR_INTERACTIONS
{
	DOOR_EMPTY,
	DOOR_HALLWAY_KITCHEN,
	DOOR_HALLWAY_HALL,
	DOOR_KITCHEN_HALLWAY,
	DOOR_HALL_HALLWAY
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

	DOOR_INTERACTIONS m_CurrentDoorTarget;
	HOUSE_ROOM m_WoodyLocationRoomTarget;
	HOUSE_ROOM m_HouseRoomTarget;
	anVec2 m_MovePoint;

	ANAnimationComposition m_DoorComposition;

	bool m_bBlockMove;

	bool m_bProcessDoor;
	bool m_bNextDoor;
	bool m_bWayback;
	IANEntity* m_pCurrentDoorEntity;
	int m_LastAnimCount;

	const char* GetDoorEventTypeFromEntity(IANEntity* pEntity);

	bool ProcessDoorInteraction(IANApi* pApi, IANEntity*& pEntity);
	void ProcessActorMove(IANApi* pApi);
	void CreateDoorEntity(IANApi* pApi, IANEntity*& ppEntity, const char* pszDoorName, anVec2 Origin);

	void KeyboardMoveInput(IANApi* pApi);

	void DrawWorld(IANApi* pApi);
	void DrawEntities(IANApi* pApi);
	void DrawStatistics(IANApi* pApi);
	void DrawUI(IANApi* pApi);
};