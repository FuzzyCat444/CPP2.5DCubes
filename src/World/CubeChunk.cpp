#include "World/CubeChunk.h"

#include <algorithm>

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

void CubeChunk::setCube(int x, int y, int z, Cube cube)
{
	if (inBounds(x, y, z))
	{
		cubes[index(x, y, z)] = cube;
	}
}

void CubeChunk::build(const Camera& camera, CubeSheet& cubeSheet)
{
	builder.clear();
	sortedCubes.clear();
	cubeSheet.orient(camera.getCubeOrientation());
	for (int z = 0; z < length; ++z)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				updateVisibility(x, y, z, camera);
			}
		}
	}
	sortedCubes.sort([&](SortableCube sc1, SortableCube sc2)
		{
			return sc1.depth > sc2.depth;
		});

	std::array<sf::Vector2f, 3> orientVecs = camera.getOrientationVectors();
	sf::Vector2f right = orientVecs[0];
	sf::Vector2f up = orientVecs[1];
	sf::Vector2f forward = orientVecs[2];
	sf::Vector2f offsetRight = (0.5f * width - 0.5f) * right;
	sf::Vector2f offsetUp = (0.5f * height - 0.5f) * up;
	sf::Vector2f offsetForward = (0.5f * length - 0.5f) * forward;

	for (auto it = sortedCubes.begin(); it != sortedCubes.end(); ++it)
	{
		CubeVisual& visual = cubeSheet.getCube(it->cube->id);
		visual.setPosition(static_cast<float>(it->x) * right - offsetRight
						 + static_cast<float>(it->y) * up - offsetUp
						 + static_cast<float>(it->z) * forward - offsetForward);
		builder.putCube(visual);
	}
}

void CubeChunk::draw(sf::RenderTarget& target, sf::RenderStates renderStates) const
{
	renderStates.transform *= getTransform();
	target.draw(builder, renderStates);
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

void CubeChunk::updateVisibility(int x, int y, int z, const Camera& camera)
{
	if (inBounds(x, y, z))
	{
		CubeTypeProperties xNegCube = getProperties(x - 1, y, z);
		CubeTypeProperties xPosCube = getProperties(x + 1, y, z);
		CubeTypeProperties yPosCube = getProperties(x, y + 1, z);
		CubeTypeProperties zNegCube = getProperties(x, y, z - 1);
		CubeTypeProperties zPosCube = getProperties(x, y, z + 1);
		bool oneCubeTransparent = xNegCube.transparent
							   || xPosCube.transparent
							   || yPosCube.transparent
							   || zNegCube.transparent
							   || zPosCube.transparent;
		const Cube& thisCube = cubes[index(x, y, z)];
		if (thisCube.id != -1 && oneCubeTransparent)
		{
			SortableCube sc;
			sc.depth = camera.depthOf(sf::Vector3f(x, y, z));
			sc.x = x;
			sc.y = y;
			sc.z = z;
			sc.cube = &thisCube;
			sortedCubes.push_back(sc);
		}
	}
}

CubeTypeProperties::CubeTypeProperties() :
	transparent(true)
{
}

CubeTypeProperties::CubeTypeProperties(bool transparent) :
	transparent(transparent)
{
}
