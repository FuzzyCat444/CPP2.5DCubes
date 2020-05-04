#ifndef CUBECHUNK_H
#define CUBECHUNK_H

#include <vector>
#include <unordered_map>
#include <cstdint>
#include <utility>

#include <SFML/Graphics.hpp>

#include "World/Cube.h"
#include "Graphics/CubeBuilder.h"

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

	void putCube(int x, int y, int z, Cube cube);

	void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const override;
private:
	enum class CubeSide : int
	{
		X_NEG = 1 << 0, 
		X_POS = 1 << 1,
		Y_POS = 1 << 2,
		Z_NEG = 1 << 3, 
		Z_POS = 1 << 4,
		ALL_SIDES_SOLID = 0
	};

	void setNeighborFlag(int x, int y, int z, CubeSide side, bool transparent);
	CubeTypeProperties getProperties(int x, int y, int z);
	bool inBounds(int x, int y, int z);
	int index(int x, int y, int z);

	int width, length, height;
	std::vector<Cube> cubes;
	std::unordered_map<CubeID, CubeTypeProperties> properties;
	CubeBuilder builder;
};

#endif