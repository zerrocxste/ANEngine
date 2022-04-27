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
	float Interpolation(float t, float start, float end);
	float LinearInterpolation(float t_start, float floating_t, float t_end, float start, float end);
}
