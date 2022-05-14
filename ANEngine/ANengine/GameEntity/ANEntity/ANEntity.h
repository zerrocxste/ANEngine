#pragma once

class ANEntity : public IANEntity
{
public:
	int GetEntityID() override;

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

	void SetEntityName(const char* szEntityName) override;
	char* GetEntityName() override;
};