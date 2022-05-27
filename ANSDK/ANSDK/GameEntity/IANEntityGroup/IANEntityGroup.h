#pragma once

class IANEntityGroup
{
public:
	std::vector<IANEntity*> m_EntityGroup;

	virtual void SetVisible(bool IsVisible) = 0;
	virtual void SetAnimationDuration(float flDuration) = 0;
	virtual void SetOrigin(anVec2 Origin) = 0;
	virtual void MovePoint(IANApi* pApi, float Speed, anVec2 Origin) = 0;
	virtual void MoveLeft(IANApi* pApi, float Speed) = 0;
	virtual void MoveRight(IANApi* pApi, float Speed) = 0;
	virtual void MoveUp(IANApi* pApi, float Speed) = 0;
	virtual void MoveDown(IANApi* pApi, float Speed) = 0;
	virtual IANEntityGroup& SortByYOrder() = 0;
	virtual void Draw(IANApi* pApi, IANWorld* pWorld) = 0;
};