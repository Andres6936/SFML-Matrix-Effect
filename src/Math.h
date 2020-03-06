#pragma once

template<typename T, typename U>
auto LinearTranslate(T a1, T b1, U a2, U b2, T x)
{
	return a2 + (b2 - a2) * (1.f * (std::clamp(x, a1, b1) - a1) / (b1 - a1));
}