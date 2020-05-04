#include "World/CubeChunk.h"

CubeChunk::CubeChunk(int width, int height, int length) :
	width(width), height(height), length(length),
	cubes(width * height * length)
{
	std::pair<CubeID, CubeTypeProperties> empty = std::make_pair(-1, CubeTypeProperties(true));
	addProperties(&empty, 1);
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
		cubes[index(x, y, z)] = cube;
		bool transparent = properties[cube.id].transparent;
		setNeighborFlag(x - 1, y, z, CubeSide::X_POS, transparent);
		setNeighborFlag(x + 1, y, z, CubeSide::X_NEG, transparent);
		setNeighborFlag(x, y - 1, z, CubeSide::Y_POS, transparent);
		setNeighborFlag(x, y, z - 1, CubeSide::Z_POS, transparent);
		setNeighborFlag(x, y, z + 1, CubeSide::Z_NEG, transparent);
		
		CubeTypeProperties xNegCube = getProperties(x - 1, y, z);
		CubeTypeProperties xPosCube = getProperties(x + 1, y, z);
		CubeTypeProperties yPosCube = getProperties(x, y + 1, z);
		CubeTypeProperties zNegCube = getProperties(x, y, z - 1);
		CubeTypeProperties zPosCube = getProperties(x, y, z + 1);
		setNeighborFlag(x, y, z, CubeSide::X_NEG, xNegCube.transparent);
		setNeighborFlag(x, y, z, CubeSide::X_POS, xPosCube.transparent);
		setNeighborFlag(x, y, z, CubeSide::Y_POS, yPosCube.transparent);
		setNeighborFlag(x, y, z, CubeSide::Z_NEG, zNegCube.transparent);
		setNeighborFlag(x, y, z, CubeSide::Z_POS, zPosCube.transparent);
	}
}

void CubeChunk::draw(sf::RenderTarget& target, sf::RenderStates renderStates) const
{
	target.draw(builder, renderStates);
}

void CubeChunk::setNeighborFlag(int x, int y, int z, CubeSide side, bool transparent)
{
	if (inBounds(x, y, z))
	{
		Cube& cube = cubes.at(index(x, y, z));
		int bit = transparent ? static_cast<int>(side) : 0;
		cube.neighborFlags &= ~bit;
		cube.neighborFlags |= bit;
	}
}

CubeTypeProperties CubeChunk::getProperties(int x, int y, int z)
{
	CubeTypeProperties props;
	if (inBounds(x, y, z))
	{
		props = properties.at(cubes[index(x, y, z)].id);
	}
	return props;
}

bool CubeChunk::inBounds(int x, int y, int z)
{
	return 0 <= x && x < width
	    && 0 <= y && y < height
		&& 0 <= z && z < length;
}

int CubeChunk::index(int x, int y, int z)
{
	return z * width * height + y * width + x;
}

CubeTypeProperties::CubeTypeProperties() :
	transparent(false)
{
}

CubeTypeProperties::CubeTypeProperties(bool transparent) :
	transparent(transparent)
{
}
