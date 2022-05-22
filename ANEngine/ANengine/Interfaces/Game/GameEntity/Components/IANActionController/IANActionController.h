#pragma once

class IANActionController
{
protected:

public:
	virtual bool IsScreenPointIntersected(IANApi* pApi, IANWorld* pWorld, anVec2 ScreenPoint) = 0;
};