#ifndef DISTANCENOISE_H
#define DISTANCENOISE_H

#include <array>

class DistanceNoise
{
public:
	DistanceNoise(long long seed, float scale);

	float sample(float x, float y);
private:
	struct GridCell
	{
		int x, y;
	};

	struct LatticePoint
	{
		float x, y, val;
	};

	float smoothstep(float t);

	LatticePoint pointFromCell(GridCell cell);

	long long pointSeed(GridCell cell);

	long long seed;
	float scale;
	std::array<GridCell, 49> neighborCells;
};

#endif