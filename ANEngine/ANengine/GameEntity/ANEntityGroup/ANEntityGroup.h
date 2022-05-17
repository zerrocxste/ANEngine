#pragma once

class ANEntityGroup : public IANEntityGroup
{
public:
	void SetVisible(bool IsVisible) override;
	void SetAnimationDuration(float flDuration) override;
	void SetOrigin(anVec2 Origin) override;
	void MovePoint(IANApi* pApi, float Speed, anVec2 Origin) override;
	void MoveLeft(IANApi* pApi, float Speed) override;
	void MoveRight(IANApi* pApi, float Speed) override;
	void MoveUp(IANApi* pApi, float Speed) override;
	void MoveDown(IANApi* pApi, float Speed) override;
	void Draw(IANApi* pApi, IANWorld* pWorld) override;
};

