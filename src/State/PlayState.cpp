#include "State/PlayState.h"

#include <SFML/Graphics.hpp>

void PlayState::handleEvent(const sf::Event& ev)
{
}

void PlayState::update()
{
}

void PlayState::draw(sf::RenderTarget& target)
{
	sf::CircleShape circle;
	circle.setRadius(50);
	circle.setFillColor(sf::Color::Red);

	sf::View view1(sf::FloatRect(0.0f, 0.0f, 400.0f, 600.0f));
	view1.setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f));
	sf::View view2(sf::FloatRect(0.0f, 0.0f, 400.0f, 600.0f));
	view2.setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));

	target.setView(view1);
	target.draw(circle);
	target.setView(view2);
	target.draw(circle);
}

void PlayState::enter()
{
}

void PlayState::exit()
{
}
