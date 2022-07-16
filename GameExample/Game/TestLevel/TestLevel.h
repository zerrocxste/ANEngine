#pragma once

#define DEBUG_LEVEL_1 1

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

enum DOOR_TYPE
{
	VERTICAL,
	HORIZONTAL
};

enum DOOR_INTERACTIONS
{
	DOOR_EMPTY,
	DOOR_HALLWAY_KITCHEN,
	DOOR_HALLWAY_HALL,
	DOOR_KITCHEN_HALLWAY,
	DOOR_HALL_HALLWAY
};

class CRoomZoneEntityData
{
public:
	CRoomZoneEntityData(
		HOUSE_ROOM HouseRoom,
		int LevelFloor) :
		m_HouseRoom(HouseRoom),
		m_LevelFloor(LevelFloor) { }

	int m_LevelFloor;
	HOUSE_ROOM m_HouseRoom;
};

class CDoorEntityData
{
public:
	CDoorEntityData(
		HOUSE_ROOM HouseRoom, 
		DOOR_TYPE DoorType,
		DOOR_INTERACTIONS DoorInteraction,
		DOOR_INTERACTIONS InvertedDoorInteraction,
		int LevelFloor) :
		m_HouseRoom(HouseRoom),
		m_DoorType(DoorType),
		m_DoorInteraction(DoorInteraction), 
		m_InvertedDoorInteraction(InvertedDoorInteraction),
		m_LevelFloor(LevelFloor) {}

	HOUSE_ROOM m_HouseRoom;
	DOOR_TYPE m_DoorType;
	DOOR_INTERACTIONS m_DoorInteraction;
	DOOR_INTERACTIONS m_InvertedDoorInteraction;
	int m_LevelFloor;
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

	template <class T> static T* GetUserData(IANEntity* pEntity)
	{
		return (T*)pEntity->GetUserDataPointer();
	}
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

	IANEntity* m_pEntityDoorZoneHallway;
	IANEntity* m_pEntityDoorZoneBathroom;
	IANEntity* m_pEntityDoorZoneKitchen;
	IANEntity* m_pEntityDoorZoneHall;

	IANEntity* m_pDoorEntityHallwayKitchen;
	IANEntity* m_pDoorEntityKitchenHallway;
	IANEntity* m_pDoorEntityHallwayHall;
	IANEntity* m_pDoorEntityHallHallway;

	DOOR_INTERACTIONS m_CurrentDoorTarget;
	HOUSE_ROOM m_HouseRoomTarget;
	anVec2 m_MovePoint;
	anVec2 m_NewMovePoint;

	ANAnimationComposition m_DoorComposition;

	bool m_bBlockMove;

	bool m_bProcessDoor;
	bool m_bNextDoor;
	bool m_bWayback;
	DOOR_INTERACTIONS m_CurrentActorInteractionDoorEnter, m_CurrentActorInteractionDoorLeave;
	DOOR_INTERACTIONS m_LastEnterActorIntercationDoor, m_LastLeaveActorIntercationDoor;
	DOOR_INTERACTIONS m_LeaveDoorEntity, m_EnterDoorEntity;
	int m_iCurrentActorFloor;
	int m_iTargetFloor;
	
	int m_LastAnimCount;

	const char* GetDoorEventTypeFromEntity(IANEntity* pEntity);

	bool ProcessDoorInteraction(IANApi* pApi, IANEntity*& pEntity);
	void ProcessActorMove(IANApi* pApi);

	void CreateRoomZoneEntity(IANApi* pApi, IANEntity*& pEntity, anVec2 RoomPos, anVec2 RoomSize, HOUSE_ROOM HouseRoom, int iLevelFloor);
	void CreateDoorEntity(IANApi* pApi, IANEntity*& pEntity, const char* pszDoorName, anVec2 Origin, DOOR_TYPE DoorType, HOUSE_ROOM HouseRoom, DOOR_INTERACTIONS DoorInteraction, DOOR_INTERACTIONS InvertedDoorInteraction, int iLevelFloor);

	void KeyboardMoveInput(IANApi* pApi);

	void DrawWorld(IANApi* pApi);
	void DrawEntities(IANApi* pApi);
	void DrawUI(IANApi* pApi);
	void DrawStatistics(IANApi* pApi);
};