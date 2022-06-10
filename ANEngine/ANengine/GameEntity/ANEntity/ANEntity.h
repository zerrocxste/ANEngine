#pragma once

class ANEntity : public IANEntity
{
	friend ANGame;
	friend ANEntityList;
public:
	int GetEntityID() override;
	char* GetEntityClassID() override;

	void SetOrigin(anVec2 Origin) override;
	anVec2 MovePoint(IANApi* pApi, float Speed, anVec2 Origin) override;
	anVec2 MoveLeft(IANApi* pApi, float Speed) override;
	anVec2 MoveRight(IANApi* pApi, float Speed) override;
	anVec2 MoveUp(IANApi* pApi, float Speed) override;
	anVec2 MoveDown(IANApi* pApi, float Speed) override;
	anVec2 GetOrigin() override;

	void SetVisible(bool IsVisible) override;
	void SetEntitySize(anVec2 EntitySize) override;
	void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) override;

	bool IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint) override;
	void SetInteractionController(IANInteractionController* pIANInteractionController) override;

	void SetEntityName(const char* szEntityName) override;
	char* GetEntityName() override;
	IANEntity& Update(IANApi* pApi) override;
};