#include "../../ANEngine.h"

double ANMathUtils::Interpolation(double t, double start, double end)
{
	return start + t * (end - start);
}

double ANMathUtils::LinearInterpolation(double t_start, double floating_t, double t_end, double start, double end)
{
	if (floating_t == t_start)
		return start;

	if (floating_t == t_end)
		return end;

	if (t_start == t_end)
		return start;

	auto t = (floating_t - t_start) / (t_end - t_start);

	return Interpolation(t, start, end);
}

anVec2 ANMathUtils::CalcDegDifferentBetweenParties(anVec2 SourceSize)
{
	return anVec2(SourceSize.x / SourceSize.y, SourceSize.y / SourceSize.x);
}

anVec2 ANMathUtils::CalcSizeAtImageAspectRatio(anVec2 OutRectSize, anVec2 SourceSize)
{
	anVec2 ret;

	auto DegOfSidesDifferent = CalcDegDifferentBetweenParties(SourceSize);

	if (OutRectSize.x < SourceSize.x)
	{
		auto DiffBetweenSrcSizeAndSizeOfContainedRect = SourceSize.x - OutRectSize.x;
		SourceSize.x = OutRectSize.x;
		SourceSize.y -= DiffBetweenSrcSizeAndSizeOfContainedRect * DegOfSidesDifferent.y;
	}

	if (OutRectSize.y < SourceSize.y)
	{
		auto DiffBetweenSrcSizeAndSizeOfContainedRect = SourceSize.y - OutRectSize.y;
		SourceSize.y = OutRectSize.y;
		SourceSize.x -= DiffBetweenSrcSizeAndSizeOfContainedRect * DegOfSidesDifferent.x;
	}

	ret = SourceSize;

	return ret;
}

anVec2 ANMathUtils::CalcPosToCenter(anVec2 OutRectSize, anVec2 SourceSize)
{
	return (OutRectSize * 0.5f) - (SourceSize * 0.5f);
}

void ANMathUtils::ZoomVerticalAligment(anVec2& SourcePos, anVec2& SourceSize, float Zoom)
{
	auto DegOfSidesDifferent = CalcDegDifferentBetweenParties(SourceSize);

	SourcePos.x -= Zoom;
	SourcePos.y -= Zoom * DegOfSidesDifferent.y;
	SourceSize.x += (Zoom * 2.f);
	SourceSize.y += (Zoom * 2.f) * DegOfSidesDifferent.y;
}

void ANMathUtils::ZoomHorizontalAligment(anVec2& SourcePos, anVec2& SourceSize, float Zoom)
{
	auto DegOfSidesDifferent = CalcDegDifferentBetweenParties(SourceSize);

	SourcePos.x -= Zoom * DegOfSidesDifferent.x;
	SourcePos.y -= Zoom;
	SourceSize.x += (Zoom * 2.f) * DegOfSidesDifferent.x;
	SourceSize.y += (Zoom * 2.f);
}

anVec2 ANMathUtils::CorrectSizeToOutRect(anVec2 OutRectSize, anVec2& SourcePos, anVec2& SourceSize)
{
	anVec2 ret;

	if (SourceSize.x < OutRectSize.x)
	{
		auto FreeSegments = (OutRectSize.x - SourceSize.x) * 0.5f;
		ZoomVerticalAligment(SourcePos, SourceSize, FreeSegments);
	}

	if (SourceSize.y < OutRectSize.y)
	{
		auto FreeSegments = (OutRectSize.y - SourceSize.y) * 0.5f;
		ZoomHorizontalAligment(SourcePos, SourceSize, FreeSegments);
	}

	return ret;
}

anVec2 ANMathUtils::PointToScreen(anVec2 WorldSize, anRect ScreenWorldRect, anVec2 PointPos)
{
	return anVec2(
		LinearInterpolation(0.f, PointPos.x, WorldSize.x, ScreenWorldRect.first.x, ScreenWorldRect.second.x),
		LinearInterpolation(0.f, PointPos.y, WorldSize.y, ScreenWorldRect.first.y, ScreenWorldRect.second.y)
	);
}

anVec2 ANMathUtils::CameraToScreen(anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2 PointWorld)
{
	return PointToScreen(WorldSize, anRect(WorldScreenPos, WorldScreenPos + WorldScreenSize), anVec2(-PointWorld.x, -PointWorld.y)) + (WorldScreenSize * 0.5f);
}

anVec2 ANMathUtils::WorldToScreen(anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2 CameraWorld, anVec2 PointWorld)
{
	return PointToScreen(WorldSize, anRect(WorldScreenPos, WorldScreenPos + WorldScreenSize), PointWorld - CameraWorld) + (WorldScreenSize * 0.5f);
}

anVec2 ANMathUtils::ScreenPointToWorld(anVec2 CameraScreen, anVec2 WorldScreenSize, anVec2 WorldSize, anVec2 ScreenPos)
{
	return anVec2
	(
		LinearInterpolation(0.f, ScreenPos.x + -CameraScreen.x, WorldScreenSize.x, 0.f, WorldSize.x),
		LinearInterpolation(0.f, ScreenPos.y + -CameraScreen.y, WorldScreenSize.y, 0.f, WorldSize.y)
	);
}

void ANMathUtils::ApplyZoom(anVec2& From, anVec2& To, float Zoom)
{
	ZoomVerticalAligment(From, To, Zoom);
}

void ANMathUtils::ClampCamera(anVec2 ScreenSize, anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2& CameraWorld)
{
	if (WorldScreenSize.x < ScreenSize.x && WorldScreenSize.y < ScreenSize.y) //fix chtobi ne kosoebilo
		return;

	auto CameraScreen = CameraToScreen(WorldSize, WorldScreenPos, WorldScreenSize, CameraWorld);

	if (CameraScreen.x > 0.f)
		CameraWorld.x += LinearInterpolation(0.f, CameraScreen.x, WorldScreenSize.x, 0.f, WorldSize.x);
	if (CameraScreen.y > 0.f)
		CameraWorld.y += LinearInterpolation(0.f, CameraScreen.y, WorldScreenSize.y, 0.f, WorldSize.y);
	if (CameraScreen.x - ScreenSize.x < -WorldScreenSize.x)
		CameraWorld.x -= LinearInterpolation(0.f, -(CameraScreen.x - ScreenSize.x - -(WorldScreenSize.x)), WorldScreenSize.x, 0.f, WorldSize.x);
	if (CameraScreen.y - ScreenSize.y < -WorldScreenSize.y)
		CameraWorld.y -= LinearInterpolation(0.f, -(CameraScreen.y - ScreenSize.y - -(WorldScreenSize.y)), WorldScreenSize.y, 0.f, WorldSize.y);
}

anRect ANMathUtils::CalcBBox(anVec2 Origin, anVec2 ObjectSize)
{
	return anRect(Origin, Origin + ObjectSize) - anVec2(ObjectSize.x * 0.5f, ObjectSize.y);
}

anRect ANMathUtils::CalcScreenBBox(ANWorldMetrics WorldMetrics, anVec2 Origin, anVec2 ObjectSize)
{
	auto bbox = ANMathUtils::CalcBBox(Origin, ObjectSize);

	return anRect(
		ANMathUtils::WorldToScreen(WorldMetrics.m_WorldSize, WorldMetrics.m_WorldScreenPos, WorldMetrics.m_WorldScreenSize, WorldMetrics.m_CameraWorld, bbox.first),
		ANMathUtils::WorldToScreen(WorldMetrics.m_WorldSize, WorldMetrics.m_WorldScreenPos, WorldMetrics.m_WorldScreenSize, WorldMetrics.m_CameraWorld, bbox.second)
	);
}
