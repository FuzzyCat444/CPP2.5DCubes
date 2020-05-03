#ifndef	CUBESHEET_H
#define CUBESHEET_H

#include <unordered_map>
#include <utility>

#include <SFML/Graphics.hpp>

#include "Graphics/CubeBuilder.h"

class CubeSheet
{
public:
	CubeSheet();

	void add(int cubeID, const CubeMaterial& material);

	void orient(const CubeOrientation& orientation, float scale);

	CubeVisual& getCube(int cubeID);
private:
	std::unordered_map<int, std::pair<CubeMaterial, CubeVisual>> cubes;
	CubeOrientation orientation;
	float scale;
};

#endif