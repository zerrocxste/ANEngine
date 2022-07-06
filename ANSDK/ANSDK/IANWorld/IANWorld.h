#pragma once

struct ANWorldMetrics
{
	anVec2 m_WorldSize;
	anVec2 m_WorldScreenPos;
	anVec2 m_WorldScreenSize;
	anVec2 m_CameraWorld;
	anVec2 m_CameraScreen;
	float m_flMapZoom;
};

class IANWorld
{
public:
	virtual ANWorldMetrics GetMetrics() = 0;

	virtual void SetWorldSize(anVec2 WorldSize) = 0;
	virtual void SetCameraToEntity(IANEntity* pEntity) = 0;
	virtual void SetCameraToPos(anVec2 Pos) = 0;
	virtual void SetZoom(float flZoom) = 0;

	virtual void Update(IANApi* pApi) = 0;
	virtual void Draw(IANApi* pApi) = 0;

	virtual IANAnimationCompositionController* GetAnimCompositionController() = 0;
};