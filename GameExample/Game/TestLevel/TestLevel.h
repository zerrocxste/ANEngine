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

enum class HOUSE_FLOOR : std::uint8_t
{
	FLOOR_UNK = -1,
	FIRST,
	SECOND
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
		HOUSE_FLOOR LevelFloor) :
		m_HouseRoom(HouseRoom),
		m_LevelFloor(LevelFloor) { }

	HOUSE_FLOOR m_LevelFloor;
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
		HOUSE_FLOOR LevelFloor) :
		m_HouseRoom(HouseRoom),
		m_DoorType(DoorType),
		m_DoorInteraction(DoorInteraction), 
		m_InvertedDoorInteraction(InvertedDoorInteraction),
		m_LevelFloor(LevelFloor) {}

	HOUSE_ROOM m_HouseRoom;
	DOOR_TYPE m_DoorType;
	DOOR_INTERACTIONS m_DoorInteraction;
	DOOR_INTERACTIONS m_InvertedDoorInteraction;
	HOUSE_FLOOR m_LevelFloor;
};

struct ActorWoodyGameData
{
	ActorWoodyGameData() :
		m_CurrentActorRoom(HOUSE_ROOM::ROOM_EMPTY),
		m_ActiveMoveTask(false),
		m_vecMovePt(anVec2()),
		m_TargetMoveRoom(HOUSE_ROOM::ROOM_EMPTY),
		m_CurrentFloor(HOUSE_FLOOR::FLOOR_UNK) {};

	HOUSE_ROOM m_CurrentActorRoom;
	bool m_ActiveMoveTask;
	anVec2 m_vecMovePt;
	HOUSE_ROOM m_TargetMoveRoom;
	HOUSE_FLOOR m_CurrentFloor;
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

	static ActorWoodyGameData& GetWoodyEntityData(IANEntity* pEntity) { return *(ActorWoodyGameData*)pEntity->GetUserDataPointer(); }
	static CRoomZoneEntityData& GetRoomEntityData(IANEntity* pEntity) { return *(CRoomZoneEntityData*)pEntity->GetUserDataPointer(); }
	static CDoorEntityData& GetDoorEntityData(IANEntity* pEntity) { return *(CDoorEntityData*)pEntity->GetUserDataPointer(); }
private:
	float m_WorldZoom;

	IANWorld* m_pWorld;
	ANAnimationComposition m_WorldComposition;

	IANEntity* m_pMainActor;
	ANAnimationComposition m_WoodyComposition;
	ANAnimationComposition m_WoodyCompositionUp;
	ANAnimationComposition m_WoodyCompositionDown;
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
	void CreateRoomZoneEntity(IANApi* pApi, IANEntity*& pEntity, anVec2 RoomPos, anVec2 RoomSize, HOUSE_ROOM HouseRoom, HOUSE_FLOOR LevelFloor);
	void CreateDoorEntity(
		IANApi* pApi, 
		IANEntity*& pEntity, 
		const char* pszDoorName, 
		anVec2 Origin, 
		DOOR_TYPE DoorType, 
		HOUSE_ROOM HouseRoom, 
		DOOR_INTERACTIONS DoorInteraction, 
		DOOR_INTERACTIONS InvertedDoorInteraction, 
		HOUSE_FLOOR LevelFloor,
		ANAnimationComposition pDoorComposition);

	void ConstructWay(IANApi* pApi, IANEntity* pActor, IANEntity* pTargetDoorEntity, IANEntity* pNextDoorTargetEntity);

	void ProcessCurrentRoomMove(IANApi* pApi);

	void ProcessMoveActorHallway(IANApi* pApi);
	void ProcessMoveActorBathroom(IANApi* pApi);
	void ProcessMoveActorKitchen(IANApi* pApi);
	void ProcessMoveActorHall(IANApi* pApi);

	void PreFrame(IANApi* pApi);
	void KeyboardMoveInput(IANApi* pApi);
	void CreateMove(IANApi* pApi);
	void DrawWorld(IANApi* pApi);
	void DrawEntities(IANApi* pApi);
	void DrawUI(IANApi* pApi);
	void DrawStatistics(IANApi* pApi);

	void SetAnimationMoveUp(IANEntity* pActor);
	void SetAnimationMoveDown(IANEntity* pActor);
	void SetAnimationMoveLeft(IANEntity* pActor);
	void SetAnimationMoveRight(IANEntity* pActor);

	float GetFloor(HOUSE_FLOOR Floor = HOUSE_FLOOR::FLOOR_UNK);
	float GetFloorFromRoom(HOUSE_ROOM Room);
};