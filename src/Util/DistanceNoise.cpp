#include "Util/DistanceNoise.h"

#include <cstdlib>
#include <cmath>

DistanceNoise::DistanceNoise(long long seed, float scale) :
	seed(seed),
	scale(scale)
{
	for (int y = 0; y < 7; ++y)
	{
		for (int x = 0; x < 7; ++x)
		{
			neighborCells[x + y * 7] = GridCell { x - 3, y - 3 };
		}
	}
}

float DistanceNoise::sample(float x, float y)
{
	x /= scale;
	y /= scale;
	GridCell cell
	{
		(int) floor(x),
		(int) floor(y)
	};

	float result = 0.0f;
	float weightSum = 0.0f;
	for (int i = 0; i < neighborCells.size(); ++i) {
		GridCell otherCell = neighborCells.at(i);
		otherCell.x += cell.x;
		otherCell.y += cell.y;
		LatticePoint otherPoint = pointFromCell(otherCell);
		float distSq = (x - otherPoint.x) * (x - otherPoint.x) + (y - otherPoint.y) * (y - otherPoint.y);
		float influence = smoothstep(fmin(4.0f, distSq) / 4.0f);
		result += influence * otherPoint.val;
		weightSum += influence;
	}
	result /= weightSum;
	
	return result;
}

float DistanceNoise::smoothstep(float t)
{
	float u = t - 1.0f;
	float u2 = u * u;
	float u4 = u2 * u2;
	float u5 = u4 * u;
	return -u5;
}

DistanceNoise::LatticePoint DistanceNoise::pointFromCell(GridCell cell)
{
	srand(pointSeed(cell));
	return LatticePoint
	{
		cell.x + rand() / static_cast<float>(RAND_MAX),
		cell.y + rand() / static_cast<float>(RAND_MAX),
		rand() / static_cast<float>(RAND_MAX)
	};
}

long long DistanceNoise::pointSeed(GridCell cell)
{
	return seed + (cell.y * 65371 + cell.x);
}
