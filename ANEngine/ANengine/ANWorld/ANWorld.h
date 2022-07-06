#pragma once

class ANWorld : public IANWorld
{
	friend IANApi;
	friend ANGame;
private:
	ANWorldMetrics m_WorldMetrics;

	bool m_bNeedUpdateCamera;
	anVec2 m_NewCameraWorld;

	IANAnimationCompositionController* m_pIANAnimationCompositionController;
public:
	ANWorldMetrics GetMetrics() override;

	void SetWorldSize(anVec2 WorldSize) override;
	void SetCameraToEntity(IANEntity* pEntity) override;
	void SetCameraToPos(anVec2 Pos) override;
	void SetZoom(float flZoom) override;

	void Update(IANApi* pApi) override;
	void Draw(IANApi* pApi) override;

	IANAnimationCompositionController* GetAnimCompositionController() override;
};