#include "Graphics/CubeSheet.h"

CubeSheet::CubeSheet() :
	orientation(0.0f, 0.0f), scale(1.0f)
{
}

void CubeSheet::add(CubeID cubeID, const CubeMaterial& material)
{
	cubes.insert(std::make_pair(cubeID, std::make_pair(CubeMaterial(material), CubeVisual(material, orientation))));
}

void CubeSheet::orient(const CubeOrientation& orientation)
{
	this->orientation = orientation;
	for (auto it = cubes.begin(); it != cubes.end(); ++it)
	{
		it->second.second = CubeVisual(it->second.first, this->orientation);
	}
}

CubeVisual& CubeSheet::getCube(CubeID cubeID)
{
	cubes.at(cubeID).second.setScale(1.0f, 1.0f);
	cubes.at(cubeID).second.setRotation(0.0f);
	cubes.at(cubeID).second.setPosition(0.0f, 0.0f);
	return cubes.at(cubeID).second;
}
