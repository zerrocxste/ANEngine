#include "../ANEngine.h"

ANWorldMetrics ANWorld::GetMetrics()
{
	return this->m_WorldMetrics;
}

void ANWorld::SetWorldSize(anVec2 WorldSize)
{
	this->m_WorldMetrics.m_WorldSize = WorldSize;
}

void ANWorld::SetCameraToEntity(IANEntity* pEntity)
{
	this->m_bNeedUpdateCamera = true;
	this->m_NewCameraWorld = pEntity->GetOrigin();
}

void ANWorld::SetCameraToPos(anVec2 Pos)
{
	this->m_bNeedUpdateCamera = true;
	this->m_NewCameraWorld = Pos;
}

void ANWorld::SetZoom(float flZoom)
{
	this->m_WorldMetrics.m_flMapZoom = flZoom;
}

void ANWorld::Update(IANApi* pApi)
{
	auto wm = &this->m_WorldMetrics;

	auto ScreenSize = pApi->GetScreenSize();

	if (this->m_bNeedUpdateCamera)
	{
		this->m_bNeedUpdateCamera = false;
		wm->m_CameraWorld = this->m_NewCameraWorld;
	}

	wm->m_WorldScreenSize = ANMathUtils::CalcSizeAtImageAspectRatio(ScreenSize, wm->m_WorldSize);
	wm->m_WorldScreenPos = ANMathUtils::CalcPosToCenter(ScreenSize, wm->m_WorldScreenSize);

	ANMathUtils::CorrectSizeToOutRect(ScreenSize, wm->m_WorldScreenPos, wm->m_WorldScreenSize);

	ANMathUtils::ApplyZoom(wm->m_WorldScreenPos, wm->m_WorldScreenSize, this->m_WorldMetrics.m_flMapZoom);

	ANMathUtils::ClampCamera(pApi->GetScreenSize(), wm->m_WorldSize, wm->m_WorldScreenPos, wm->m_WorldScreenSize, wm->m_CameraWorld);

	wm->m_CameraScreen = ANMathUtils::CameraToScreen(wm->m_WorldSize, wm->m_WorldScreenPos, wm->m_WorldScreenSize, wm->m_CameraWorld);
}

void ANWorld::Draw(IANApi* pApi, ANImageID pImageID)
{
	auto wm = &this->m_WorldMetrics;

	pApi->DrawImage(pImageID, wm->m_CameraScreen, wm->m_WorldScreenSize, 1.f);
}