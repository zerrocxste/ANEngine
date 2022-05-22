#pragma once

class IANAnimationController
{
protected:
	bool m_bIsOccluded;
public:
	virtual void SetVisible(bool IsVisible) = 0;
	virtual void DrawFromComposition(IANApi* pApi, IANWorld* pWorld) = 0;
};