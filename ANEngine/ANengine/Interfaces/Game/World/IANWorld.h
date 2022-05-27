#pragma once

class IANWorld
{
protected:
	ANWorldMetrics m_WorldMetrics;
	anVec2 m_NewCameraWorld;
	bool m_bNeedUpdateCamera;
public:
	IANAnimationCompositionController* m_pIANAnimationCompositionController;

	virtual ANWorldMetrics GetMetrics() = 0;
	virtual void SetWorldSize(anVec2 WorldSize) = 0;
	virtual void SetCameraToEntity(IANEntity* pEntity) = 0;
	virtual void SetCameraToPos(anVec2 Pos) = 0;
	virtual void SetZoom(float flZoom) = 0;
	virtual void Update(IANApi* pApi) = 0;
	virtual void Draw(IANApi* pApi) = 0;
};