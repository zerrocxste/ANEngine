#pragma once

class ANWorld : public IANWorld
{
	friend IANApi;
	friend ANGame;
public:
	ANWorldMetrics GetMetrics() override;
	void SetWorldSize(anVec2 WorldSize) override;
	void SetCameraToEntity(IANEntity* pEntity) override;
	void SetCameraToPos(anVec2 Pos) override;
	void SetZoom(float flZoom) override;
	void Update(IANApi* pApi) override;
	void Draw(IANApi* pApi, ANImageID pImageID) override;
};