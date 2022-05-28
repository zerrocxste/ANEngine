#pragma once

class IANMovementController
{
protected:
	anVec2 m_Origin;
public:
	virtual void SetOrigin(anVec2 Origin) = 0;
	virtual anVec2 MovePoint(IANApi* pApi, float Speed, anVec2 Origin) = 0;
	virtual anVec2 MoveLeft(IANApi* pApi, float Speed) = 0;
	virtual anVec2 MoveRight(IANApi* pApi, float Speed) = 0;
	virtual anVec2 MoveUp(IANApi* pApi, float Speed) = 0;
	virtual anVec2 MoveDown(IANApi* pApi, float Speed) = 0;
	virtual anVec2 GetOrigin() = 0;
};