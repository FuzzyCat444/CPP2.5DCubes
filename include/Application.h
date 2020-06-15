#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

#include "Graphics/Camera.h"
#include "Graphics/CubeSheet.h"
#include "World/CubeChunk.h"
#include "Util/DistanceNoise.h"

class Application : private sf::Drawable
{
public:
	Application();

	void run();
private:
	void init();

	void handleEvent(const sf::Event& ev);

	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum class Cubes
	{
		EMPTY = -1,
		STONE,
		DIRT,
		GRASS,
		WATER,
		SAND,
		WOOD,
		LEAVES,
		COUNT
	};

	CubeID cbID(Cubes type);

	sf::Texture cubeSheetTexture;
	Camera camera;
	CubeSheet cubeSheet;
	CubeChunk chunk;
	DistanceNoise noise;

	float zoom;
	float zoomVel;

	bool qPressed;
	bool ePressed;
	float spin;
	float spinVel;

	bool wPressed;
	bool aPressed;
	bool sPressed;
	bool dPressed;
	float x;
	float y;
	float xVel;
	float yVel;
};

#endif


