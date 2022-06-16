#pragma once

class IANMovementController
{
public:
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
};