#pragma once

class ANEntity : public IANEntity
{
	friend ANGame;
public:
	int GetEntityID() override;
	char* GetEntityClassID() override;

	void SetOrigin(anVec2 Origin) override;
	void MovePoint(IANApi* pApi, float Speed, anVec2 Origin) override;
	void MoveLeft(IANApi* pApi, float Speed) override;
	void MoveRight(IANApi* pApi, float Speed) override;
	void MoveUp(IANApi* pApi, float Speed) override;
	void MoveDown(IANApi* pApi, float Speed) override;
	anVec2 GetOrigin() override;

	void SetAnimationDuration(float flDuration) override;
	bool IsNeedUpdateAnimation(IANApi* pApi) override;
	void SetVisible(bool IsVisible) override;
	void SetAnimationComposition(ANAnimationComposition AnimationComposition) override;
	void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) override;

	void SetEntityName(const char* szEntityName) override;
	char* GetEntityName() override;
};