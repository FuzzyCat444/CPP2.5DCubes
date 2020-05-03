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
	bool transparent;
};

class CubeChunk : public sf::Drawable
{
public:
	CubeChunk(int width, int height, int length);

	void addProperties(std::pair<CubeID, CubeTypeProperties> propertiesList[], int count);

	void putCube(int x, int y, int z, Cube cube);

	void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const override;
private:
	enum class CubeSide
	{
		X_NEG, X_POS, Y_NEG, Y_POS, Z_NEG, Z_POS
	};

	void setNeighborFlag(int x, int y, int z, CubeSide side, bool solid);
	bool inBounds(int x, int y, int z);

	int width, length, height;
	std::vector<Cube> cubes;
	std::unordered_map<CubeID, CubeTypeProperties> properties;
	CubeBuilder builder;
};

#endif