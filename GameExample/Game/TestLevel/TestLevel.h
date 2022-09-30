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

enum HOUSE_ROOM : std::uint8_t
{
	ROOM_EMPTY,
	HALLWAY,
	BATHROOM,
	KITCHEN,
	HALL
};

enum DOOR_TYPE : std::uint8_t
{
	VERTICAL,
	HORIZONTAL
};

enum DOOR_INTERACTIONS : std::uint8_t
{
	DOOR_EMPTY,

	DOOR_HALLWAY_KITCHEN,
	DOOR_HALLWAY_HALL,
	DOOR_KITCHEN_HALLWAY,
	DOOR_HALL_HALLWAY,

	DOOR_HALL_KITCHEN,
	DOOR_KITCHEN_HALL,

	DOOR_HALLWAY_BATHROOM,
	DOOR_BATHROOM_HALLWAY
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

	struct actWoodyGameData
	{
		actWoodyGameData() : 
			m_CurrentActorFloor(HOUSE_ROOM::ROOM_EMPTY),
			m_ActiveMoveTask(false), 
			m_vecMovePt(anVec2()), 
			m_TargetMoveRoom(HOUSE_ROOM::ROOM_EMPTY) {};

		HOUSE_ROOM m_CurrentActorFloor;
		bool m_ActiveMoveTask;
		anVec2 m_vecMovePt;
		HOUSE_ROOM m_TargetMoveRoom;
	};

	static actWoodyGameData& GetWoodyEntityData(IANEntity* pEntity) { return *(actWoodyGameData*)pEntity->GetUserDataPointer(); }
	static CRoomZoneEntityData& GetRoomEntityData(IANEntity* pEntity) { return *(CRoomZoneEntityData*)pEntity->GetUserDataPointer(); }
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
	ANAnimationComposition m_WoodyDoorSideLeftEnter;
	ANAnimationComposition m_WoodyDoorSideRightEnter;
	ANAnimationComposition m_DoorComposition;
	ANAnimationComposition m_DoorCompositionLeft;
	ANAnimationComposition m_DoorCompositionRight;

	IANEntity* m_pEntityDoorZoneHallway;
	IANEntity* m_pEntityDoorZoneBathroom;
	IANEntity* m_pEntityDoorZoneKitchen;
	IANEntity* m_pEntityDoorZoneHall;

	IANEntity* m_pDoorEntityHallwayKitchen;
	IANEntity* m_pDoorEntityKitchenHallway;
	IANEntity* m_pDoorEntityHallwayHall;
	IANEntity* m_pDoorEntityHallHallway;

	IANEntity* m_pDoorEntityHallKitchen;
	IANEntity* m_pDoorEntityKitchenHall;

	IANEntity* m_pDoorEntityHallwayBathroom;
	IANEntity* m_pDoorEntityBathroomHallway;

	const char* GetDoorEventTypeFromEntity(IANEntity* pEntity);

	void CreateActorEntity(IANApi* pApi, const char* pszActorName);
	void CreateRoomZoneEntity(IANApi* pApi, IANEntity*& pEntity, anVec2 RoomPos, anVec2 RoomSize, HOUSE_ROOM HouseRoom, int iLevelFloor);
	void CreateDoorEntity(
		IANApi* pApi, 
		IANEntity*& pEntity, 
		const char* pszDoorName, 
		anVec2 Origin, 
		DOOR_TYPE DoorType, 
		HOUSE_ROOM HouseRoom, 
		DOOR_INTERACTIONS DoorInteraction, 
		DOOR_INTERACTIONS InvertedDoorInteraction, 
		int iLevelFloor, 
		ANAnimationComposition pDoorComposition);

	void ProcessMoveActorHall(IANApi* pApi);

	void PreFrame(IANApi* pApi);
	void KeyboardMoveInput(IANApi* pApi);
	void CreateMove(IANApi* pApi);
	void DrawWorld(IANApi* pApi);
	void DrawEntities(IANApi* pApi);
	void DrawUI(IANApi* pApi);
	void DrawStatistics(IANApi* pApi);
};