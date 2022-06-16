#pragma once

class IANAnimationController
{
public:
	virtual void SetVisible(bool IsVisible) = 0;
	virtual void SetEntitySize(anVec2 EntitySize) = 0;
	virtual void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) = 0;
};