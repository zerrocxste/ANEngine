#pragma once

class ANEntity : public IANEntity
{
	friend ANGame;
	friend ANEntityList;
private:
	int m_ID;
	char* m_szEntityClassID;

	anVec2 m_Origin;

	anVec2 m_EntitySize;
	bool m_bIsOccluded;

	IANInteractionController* m_pIANInteractionControllerUserCallback;

	char* m_szEntityName;

	IANAnimationCompositionController* m_pAnimCompositionController;

	void* m_pUserData;
public:
	int GetEntityID() override;
	char* GetEntityClassID() override;

	void SetOrigin(anVec2 Origin) override;
	anVec2 MovePoint(IANApi* pApi, float Speed, anVec2 Origin) override;
	anVec2 MovePointLeft(IANApi* pApi, float Speed, float XValue) override;
	anVec2 MovePointRight(IANApi* pApi, float Speed, float XValue) override;
	anVec2 MovePointUp(IANApi* pApi, float Speed, float YValue) override;
	anVec2 MovePointDown(IANApi* pApi, float Speed, float YValue) override;
	anVec2 MoveHorizontal(IANApi* pApi, float Speed, float XValue) override;
	anVec2 MoveVertical(IANApi* pApi, float Speed, float YValue) override;
	anVec2 MoveLeft(IANApi* pApi, float Speed) override;
	anVec2 MoveRight(IANApi* pApi, float Speed) override;
	anVec2 MoveUp(IANApi* pApi, float Speed) override;
	anVec2 MoveDown(IANApi* pApi, float Speed) override;
	anVec2 GetOrigin() override;

	void SetVisible(bool IsVisible) override;
	bool GetVisible() override;
	void SetEntitySize(anVec2 EntitySize) override;
	anVec2 GetEntitySize() override;
	anVec2 CalcEntitySize(IANApi* pApi) override;

	void DrawRectRegion(IANApi* pApi, IANWorld* pWorld, anColor Color) override;
	void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) override;

	bool IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint) override;
	void SetInteractionController(IANInteractionController* pIANInteractionController) override;

	void SetEntityName(const char* szEntityName) override;
	char* GetEntityName() override;
	IANAnimationCompositionController* GetAnimCompositionController() override;
	IANEntity& Update(IANApi* pApi) override;

	void SetUserDataPointer(void* pUserData) override;
	void* GetUserDataPointer() override;
};