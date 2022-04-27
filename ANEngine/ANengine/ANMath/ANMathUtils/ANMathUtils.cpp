#include "../../ANEngine.h"

float ANMathUtils::Interpolation(float t, float start, float end)
{
	return start + t * (end - start);
}

float ANMathUtils::LinearInterpolation(float t_start, float floating_t, float t_end, float start, float end)
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