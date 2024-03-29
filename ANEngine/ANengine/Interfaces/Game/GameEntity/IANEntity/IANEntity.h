#pragma once

const float SPEED_FRAME = -1.f;

enum ANDirectionMoveFlags : int //REQUIRED AND IMPORTANT
{
	MOVE_NO = 0,
	MOVE_UP = 1 << 0,
	MOVE_DOWN = 1 << 1,
	MOVE_LEFT = 1 << 2,
	MOVE_RIGHT = 1 << 3
};

static ANDirectionMoveFlags& operator|=(ANDirectionMoveFlags& _this, const ANDirectionMoveFlags v)
{
	*(int*)&_this |= v;
	return _this;
}

struct ANEntityMoveInfo
{
	ANDirectionMoveFlags m_EntityDirectionFlags;
	float m_flSpeed;
};

class IANEntity
{
public:
	using fOnReleaseUserData = void(__fastcall*)(void* _this);

	virtual int GetEntityID() = 0;
	virtual char* GetEntityClassID() = 0;

	virtual void SetOrigin(anVec2 Origin) = 0;
	virtual anVec2 MovePoint(IANApi* pApi, float Speed, anVec2 Origin) = 0;
	virtual anVec2 MovePointLeft(IANApi* pApi, float Speed, float XValue) = 0;
	virtual anVec2 MovePointRight(IANApi* pApi, float Speed, float XValue) = 0;
	virtual anVec2 MovePointUp(IANApi* pApi, float Speed, float YValue) = 0;
	virtual anVec2 MovePointDown(IANApi* pApi, float Speed, float YValue) = 0;
	virtual anVec2 MoveHorizontal(IANApi* pApi, float Speed, float XValue) = 0;
	virtual anVec2 MoveVertical(IANApi* pApi, float Speed, float YValue) = 0;
	virtual anVec2 MoveLeft(IANApi* pApi, float Speed) = 0;
	virtual anVec2 MoveRight(IANApi* pApi, float Speed) = 0;
	virtual anVec2 MoveUp(IANApi* pApi, float Speed) = 0;
	virtual anVec2 MoveDown(IANApi* pApi, float Speed) = 0;
	virtual anVec2 GetOrigin() = 0;

	virtual ANEntityMoveInfo GetMoveInfo() = 0;

	virtual void SetVisible(bool IsVisible) = 0;
	virtual bool GetVisible() = 0;
	virtual void SetEntitySize(anVec2 EntitySize) = 0;
	virtual anVec2 GetEntitySize() = 0;
	virtual anVec2 CalcEntitySize(IANApi* pApi) = 0;

	virtual anRect CalcBBox(IANApi* pApi) = 0;
	virtual anRect CalcScreenBBox(IANApi* pApi, IANWorld* pWorld) = 0;

	virtual void DrawRectRegion(IANApi* pApi, IANWorld* pWorld, anColor Color) = 0;
	virtual void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) = 0;

	virtual bool IsWorldPointIntersected(IANApi* pApi, anVec2 WorldPoint) = 0;
	virtual bool IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint) = 0;

	virtual void SetInteractionController(IANInteractionController* pIANInteractionController) = 0;

	virtual void SetEntityName(const char* szEntityName) = 0;
	virtual char* GetEntityName() = 0;

	virtual IANAnimationCompositionController* GetAnimCompositionController() = 0;
	virtual void AddDefaultAnimationComposition(IANApi* pApi, ANAnimationComposition AnimationComposition, float flAnimationDuration) = 0;
	virtual void DeleteDefaultAnimationComposition(IANApi* pApi) = 0;

	virtual IANEntity& Update(IANApi* pApi) = 0;

	virtual void SetUserDataPointer(void* pUserData) = 0;
	virtual void SetOnReleaseUserData(fOnReleaseUserData pfOnReleaseUserData) = 0;
	virtual void* GetUserDataPointer() = 0;
};