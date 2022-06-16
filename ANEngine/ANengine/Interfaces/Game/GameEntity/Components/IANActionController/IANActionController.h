#pragma once

class IANActionController
{
public:
	virtual bool IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint) = 0;

	virtual void SetInteractionController(IANInteractionController* pIANInteractionController) = 0;
};