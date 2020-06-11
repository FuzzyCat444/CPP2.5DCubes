#include "Application.h"

#include <utility>

#include "Util/ColorShade.h"

Application::Application() :
	chunk(8, 9, 8)
{
	std::pair<CubeID, CubeTypeProperties> props[static_cast<int>(Cubes::COUNT)] =
	{
		std::make_pair(cbID(Cubes::STONE), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::DIRT), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::GRASS), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::WATER), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::SAND), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::WOOD), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::LEAVES), CubeTypeProperties(true)),
	};
	chunk.addProperties(props, 7);
	for (int z = 0; z < 8; ++z)
	{
		for (int x = 0; x < 8; ++x)
		{
			chunk.setCube(x, 0, z, Cube(cbID(Cubes::STONE)));
			chunk.setCube(x, 1, z, Cube(cbID(Cubes::DIRT)));
			chunk.setCube(x, 2, z, Cube(cbID(Cubes::GRASS)));
		}
	}
	chunk.setCube(1, 2, 1, Cube(cbID(Cubes::SAND)));
	chunk.setCube(2, 2, 1, Cube(cbID(Cubes::SAND)));
	chunk.setCube(3, 2, 1, Cube(cbID(Cubes::SAND)));
	chunk.setCube(4, 2, 1, Cube(cbID(Cubes::SAND)));
	chunk.setCube(1, 2, 2, Cube(cbID(Cubes::SAND)));
	chunk.setCube(1, 2, 3, Cube(cbID(Cubes::SAND)));
	chunk.setCube(1, 2, 4, Cube(cbID(Cubes::SAND)));
	chunk.setCube(2, 2, 4, Cube(cbID(Cubes::SAND)));
	chunk.setCube(3, 2, 4, Cube(cbID(Cubes::SAND)));
	chunk.setCube(4, 2, 4, Cube(cbID(Cubes::SAND)));
	chunk.setCube(4, 2, 3, Cube(cbID(Cubes::SAND)));
	chunk.setCube(4, 2, 2, Cube(cbID(Cubes::SAND)));
	chunk.setCube(2, 2, 2, Cube(cbID(Cubes::WATER)));
	chunk.setCube(2, 2, 3, Cube(cbID(Cubes::WATER)));
	chunk.setCube(3, 2, 2, Cube(cbID(Cubes::WATER)));
	chunk.setCube(3, 2, 3, Cube(cbID(Cubes::WATER)));

	for (int y = 5; y < 5 + 3; ++y)
	{
		for (int z = 4; z < 4 + 3; ++z)
		{
			for (int x = 4; x < 4 + 3; ++x)
			{
				chunk.setCube(x, y, z, Cube(cbID(Cubes::LEAVES)));
			}
		}
	}
	chunk.setCube(5, 8, 5, Cube(cbID(Cubes::LEAVES)));
	chunk.setCube(5, 3, 5, Cube(cbID(Cubes::WOOD)));
	chunk.setCube(5, 4, 5, Cube(cbID(Cubes::WOOD)));
	chunk.setCube(5, 5, 5, Cube(cbID(Cubes::WOOD)));

	camera.setPitch(30.0f);
}

void Application::run()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Isometric Cubes");
	window.setFramerateLimit(60);
	sf::View view;
	view.setSize(sf::Vector2f(800, -600));
	view.setCenter(400, 300);
	window.setView(view);

	init();
	while (window.isOpen())
	{
		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
			else
				handleEvent(ev);
		}
		update();

		window.clear();
		window.draw(*this);
		window.display();
	}
}

void Application::init()
{
	cubeSheetTexture.loadFromFile("cubesheettemp.png");
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
	cubeSheet.add(cbID(Cubes::STONE), mat);
	mat.indexX = 0;
	mat.indexY = 1;
	cubeSheet.add(cbID(Cubes::DIRT), mat);
	mat.indexX = 0;
	mat.indexY = 2;
	cubeSheet.add(cbID(Cubes::GRASS), mat);
	mat.indexX = 0;
	mat.indexY = 3;
	cubeSheet.add(cbID(Cubes::WATER), mat);
	mat.indexX = 1;
	mat.indexY = 0;
	cubeSheet.add(cbID(Cubes::SAND), mat);
	mat.indexX = 1;
	mat.indexY = 1;
	cubeSheet.add(cbID(Cubes::WOOD), mat);
	mat.indexX = 1;
	mat.indexY = 2;
	cubeSheet.add(cbID(Cubes::LEAVES), mat);
}

void Application::handleEvent(const sf::Event& ev) 
{
	static float y = 0.0f;
	if (ev.type == sf::Event::MouseMoved)
	{
		camera.rotatePitch((ev.mouseMove.y - y) * 0.5f);
		y = ev.mouseMove.y;
	}
}

void Application::update()
{
	camera.rotateYaw(1.0f);
	chunk.setScale(50.0f, 50.0f);
	chunk.setPosition(400.0f, 350.0f);
	chunk.build(camera, cubeSheet);
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &cubeSheetTexture;
	target.draw(chunk, states);
}

CubeID Application::cbID(Cubes type)
{
	switch (type)
	{
	case Cubes::EMPTY:
		return -1;
		break;
	case Cubes::STONE:
		return 0;
		break;
	case Cubes::DIRT:
		return 1;
		break;
	case Cubes::GRASS:
		return 2;
		break;
	case Cubes::WATER:
		return 3;
		break;
	case Cubes::SAND:
		return 4;
	case Cubes::WOOD:
		return 5;
		break;
	case Cubes::LEAVES:
		return 6;
		break;
		break;
	default:
		return -1;
	}
}