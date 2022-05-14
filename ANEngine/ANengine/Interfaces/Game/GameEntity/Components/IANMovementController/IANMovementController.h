#pragma once

class IANMovementController
{
protected:
	anVec2 m_Origin;
public:
	virtual void SetOrigin(anVec2 Origin) = 0;
	virtual void MovePoint(IANApi* pApi, float Speed, anVec2 Origin) = 0;
	virtual void MoveLeft(IANApi* pApi, float Speed) = 0;
	virtual void MoveRight(IANApi* pApi, float Speed) = 0;
	virtual void MoveUp(IANApi* pApi, float Speed) = 0;
	virtual void MoveDown(IANApi* pApi, float Speed) = 0;
	virtual anVec2 GetOrigin() = 0;
};