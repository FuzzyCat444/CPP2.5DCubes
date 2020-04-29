#include "Application.h"

#include <utility>

#include <SFML/Graphics.hpp>

Application::Application() :
	stateManager(static_cast<int>(StateType::STATE_PLAY))
{
	std::unique_ptr<State> playState = std::make_unique<PlayState>();
	stateManager.addState(static_cast<int>(StateType::STATE_PLAY), playState);
}

void Application::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Isometric Cubes");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
			stateManager.handleEvent(ev);
		}
		stateManager.update();

		window.clear();
		stateManager.draw(window);
		window.display();

		stateManager.finishFrame();
	}
}
