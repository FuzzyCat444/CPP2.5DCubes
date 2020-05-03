#include "World/CubeChunk.h"

CubeChunk::CubeChunk(int width, int height, int length) :
	width(width), height(height), length(length),
	cubes(width * height * length)
{
}

void CubeChunk::addProperties(std::pair<CubeID, CubeTypeProperties> propertiesList[], int count)
{
	for (int i = 0; i < count; ++i)
	{
		properties.insert(propertiesList[i]);
	}
}

void CubeChunk::putCube(int x, int y, int z, Cube cube)
{
	if (inBounds(x, y, z))
	{
		cubes[z * width * height + y * width + x] = cube;
		updateFlags(x, y, z);
		updateFlags(x - 1, y, z);
		updateFlags(x + 1, y, z);
		updateFlags(x, y - 1, z);
		updateFlags(x, y + 1, z);
		updateFlags(x, y, z - 1);
		updateFlags(x, y, z + 1);
	}
}

void CubeChunk::draw(sf::RenderTarget& target, sf::RenderStates renderStates) const
{

}

void setNeighborFlag(int x, int y, int z, CubeSide side, bool solid)
{
	if (inBounds(x, y, z))
	{

	}
}

bool CubeChunk::inBounds(int x, int y, int z)
{
	return 0 <= x && x < width
	    && 0 <= y && y < height
		&& 0 <= z && z < length;
}

CubeTypeProperties::CubeTypeProperties() :
	transparent(false)
{
}
