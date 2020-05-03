#include "State/PlayState.h"

#include <SFML/Graphics.hpp>

#include "Util/ColorShade.h"

PlayState::PlayState()
{
}

void PlayState::init()
{
	cubeSheetTexture.loadFromFile("cubesheet.png");
	CubeMaterial mat =
	{
		0, 0, 16,
		shaded(sf::Color::White, 1.0f),
		shaded(sf::Color::White, 0.8f),
		shaded(sf::Color::White, 0.6f),
		shaded(sf::Color::White, 0.4f),
		shaded(sf::Color::White, 0.6f)
	};
	mat.indexX = 0;
	mat.indexY = 0;
	cubeSheet.add(0, mat);
	mat.indexX = 0;
	mat.indexY = 1;
	cubeSheet.add(1, mat);
	mat.indexX = 1;
	mat.indexY = 0;
	cubeSheet.add(2, mat);
}

void PlayState::handleEvent(const sf::Event& ev)
{
}

void PlayState::update()
{
	static float x = 0.0f;
	x++;
	cubeBuilder.clear();
	cubeSheet.orient(CubeOrientation(x, 30.0f), 150.0f);

	CubeVisual& cube = cubeSheet.getCube(0); // Grass
	cube.setPosition(150.0f, 150.0f);
	cubeBuilder.putCube(cube);

	cube = cubeSheet.getCube(1); // Stone
	cube.setPosition(400.0f, 250.0f);
	cubeBuilder.putCube(cube);

	cube = cubeSheet.getCube(2); // Wood
	cube.setPosition(650.0f, 350.0f);
	cubeBuilder.putCube(cube);
}

void PlayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &cubeSheetTexture;
	target.draw(cubeBuilder, states);
}

void PlayState::enter()
{
}

void PlayState::exit()
{
}
