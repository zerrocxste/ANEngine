#pragma once

namespace ANMathUtils
{
	template<class T>
	T Clamp(T v, T min, T max)
	{
		if (v < min)
			return min;

		if (v > max)
			return max;

		return v;
	}

	double Interpolation(double t, double start, double end);
	double LinearInterpolation(double t_start, double floating_t, double t_end, double start, double end);
	anVec2 CalcDegDifferentBetweenParties(anVec2 SourceSize);
	anVec2 CalcSizeAtImageAspectRatio(anVec2 OutRectSize, anVec2 SourceSize);
	anVec2 CalcPosToCenter(anVec2 OutRectSize, anVec2 SourceSize);
	void ZoomVerticalAligment(anVec2& SourcePos, anVec2& SourceSize, float Zoom);
	void ZoomHorizontalAligment(anVec2& SourcePos, anVec2& SourceSize, float Zoom);
	anVec2 CorrectSizeToOutRect(anVec2 OutRectSize, anVec2& SourcePos, anVec2& SourceSize);
	anVec2 PointToScreen(anVec2 WorldSize, anRect ScreenWorldRect, anVec2 PointPos);
	anVec2 CameraToScreen(anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2 PointWorld);
	anVec2 WorldToScreen(anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2 CameraWorld, anVec2 PointWorld);
	anVec2 ScreenPointToWorld(anVec2 CameraScreen, anVec2 WorldScreenSize, anVec2 WorldSize, anVec2 ScreenPos);
	void ApplyZoom(anVec2& From, anVec2& To, float Zoom);
	void ClampCamera(anVec2 ScreenSize, anVec2 WorldSize, anVec2 WorldScreenPos, anVec2 WorldScreenSize, anVec2& CameraWorld);
	anRect CalcBBox(anVec2 Origin, anVec2 ObjectSize);
	anRect CalcScreenBBox(ANWorldMetrics WorldMetrics, anVec2 Origin, anVec2 ObjectSize);
}
