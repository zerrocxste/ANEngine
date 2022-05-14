#pragma once

class IANAnimationController
{
protected:
	float m_flAnimationTime;
	float m_flAnimationDuration;
	bool m_bIsVisible;
public:
	virtual void SetAnimationDuration(float flDuration) = 0;
	virtual bool IsNeedUpdateAnimation(IANApi* pApi) = 0;
	virtual void SetVisible(bool IsVisible) = 0;
};