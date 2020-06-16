#ifndef CUBECHUNK_H
#define CUBECHUNK_H

#include <vector>
#include <list>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <utility>

#include <SFML/Graphics.hpp>

#include "World/Cube.h"
#include "Graphics/CubeBuilder.h"
#include "Graphics/CubeSheet.h"
#include "Graphics/Camera.h"

struct CubeTypeProperties
{
	CubeTypeProperties();
	CubeTypeProperties(bool transparent);
	bool transparent;
};

class CubeChunk : public sf::Drawable, public sf::Transformable
{
public:
	CubeChunk(int width, int height, int length);

	void addProperties(std::pair<CubeID, CubeTypeProperties> propertiesList[], int count);

	void setCube(int x, int y, int z, Cube cube);

	Cube getCube(int x, int y, int z);

	void build(const Camera& camera, CubeSheet& cubeSheet);

	void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const override;
private:
	CubeTypeProperties getProperties(int x, int y, int z);
	bool inBounds(int x, int y, int z);
	int index(int x, int y, int z);
	void updateVisibility(int x, int y, int z, const Camera& camera);

	int width, length, height;
	std::vector<Cube> cubes;
	std::unordered_map<CubeID, CubeTypeProperties> properties;

	struct SortableCube
	{
		float depth;
		int x, y, z;
		const Cube* cube;
	};
	void positionSortedCube(SortableCube& cube, const Camera& camera);

	bool needsNeighborCheck;
	std::list<SortableCube> sortedCubes;
	CubeBuilder builder;
};

#endif