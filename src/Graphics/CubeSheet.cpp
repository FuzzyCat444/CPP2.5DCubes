#include "Graphics/CubeSheet.h"

CubeSheet::CubeSheet() :
	orientation(0.0f, 0.0f), scale(1.0f)
{
}

void CubeSheet::add(int cubeID, const CubeMaterial& material)
{
	cubes.insert(std::make_pair(cubeID, std::make_pair(CubeMaterial(material), CubeVisual(material, orientation))));
}

void CubeSheet::orient(const CubeOrientation& orientation, float scale)
{
	this->orientation = orientation;
	this->scale = scale;
	for (auto it = cubes.begin(); it != cubes.end(); ++it)
	{
		it->second.second = CubeVisual(it->second.first, this->orientation);
	}
}

CubeVisual& CubeSheet::getCube(int cubeID)
{
	cubes.at(cubeID).second.setScale(scale, scale);
	cubes.at(cubeID).second.setRotation(0.0f);
	cubes.at(cubeID).second.setPosition(0.0f, 0.0f);
	return cubes.at(cubeID).second;
}
