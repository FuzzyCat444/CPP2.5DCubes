#include "State/PlayState.h"

#include <SFML/Graphics.hpp>

PlayState::PlayState()
{
}

void PlayState::init()
{
	furnace.loadFromFile("furnace.png");
}

void PlayState::handleEvent(const sf::Event& ev)
{
}

void PlayState::update()
{
	static float x = 0.0f;
	x++;
	cubeBuilder.clear();
	CubeVisual cube(CubeMaterial(0, 0, 16, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White), CubeOrientation(x, 30.0f));
	cube.scale(100.0f, 100.0f);
	cube.move(200.0f, 200.0f);
	cubeBuilder.putCube(cube);
	cube.move(100.0f, 0.0f);
	cubeBuilder.putCube(cube);
}

void PlayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &furnace;
	target.draw(cubeBuilder, states);
}

void PlayState::enter()
{
}

void PlayState::exit()
{
}
