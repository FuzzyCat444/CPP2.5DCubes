#include "State/PlayState.h"

#include <SFML/Graphics.hpp>

PlayState::PlayState()
{
}

void PlayState::init()
{
	furnace.loadFromFile("furnace.png");
	cube = Cube(CubeMaterial(16.0f, &furnace, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White), CubeOrientation(30.0f, 30.0f));
}

void PlayState::handleEvent(const sf::Event& ev)
{
}

void PlayState::update()
{
}

void PlayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(cube, states);
}

void PlayState::enter()
{
}

void PlayState::exit()
{
}
