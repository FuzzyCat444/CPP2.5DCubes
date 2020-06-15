#include "Application.h"

#include <utility>
#include <cmath>
#include <ctime>

#include "Util/ColorShade.h"
#include "Util/MathFunctions.h"

Application::Application() :
	chunk(50, 20, 50),
	noise(time(NULL), 10.0f),
	zoom(0.2f),
	zoomVel(0.0f),
	qPressed(false),
	ePressed(false),
	spin(45.0f),
	spinVel(0.0f),
	wPressed(false),
	aPressed(false),
	sPressed(false),
	dPressed(false),
	x(0.0f),
	y(0.0f),
	xVel(0.0f),
	yVel(0.0f)
{
	std::pair<CubeID, CubeTypeProperties> props[static_cast<int>(Cubes::COUNT)] =
	{
		std::make_pair(cbID(Cubes::STONE), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::DIRT), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::GRASS), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::WATER), CubeTypeProperties(true)),
		std::make_pair(cbID(Cubes::SAND), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::WOOD), CubeTypeProperties(false)),
		std::make_pair(cbID(Cubes::LEAVES), CubeTypeProperties(true)),
	};
	chunk.addProperties(props, 7);

	for (int z = 0; z < 50; ++z)
	{
		for (int x = 0; x < 50; ++x)
		{
			chunk.setCube(x, (int) (noise.sample(x, z) * 20.0f), z, Cube(cbID(Cubes::STONE)));
		}
	}
	
	/*
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
	*/
	

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
	sf::Color col(255, 255, 255, 20);
	CubeMaterial waterMat =
	{
		0, 0, 16,
		col, col, col, col, col
	};
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
	cubeSheet.add(cbID(Cubes::WATER), waterMat);
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
		camera.setPitch(ev.mouseMove.y / 600.0f * 90.0f);
		y = ev.mouseMove.y;
	}
	if (ev.type == sf::Event::MouseWheelScrolled)
	{
		zoomVel += ev.mouseWheelScroll.delta * 0.01f;
	}
	if (ev.type == sf::Event::KeyPressed)
	{
		if (ev.key.code == sf::Keyboard::Q)
			qPressed = true;
		if (ev.key.code == sf::Keyboard::E)
			ePressed = true;
		if (ev.key.code == sf::Keyboard::W)
			wPressed = true;
		if (ev.key.code == sf::Keyboard::A)
			aPressed = true;
		if (ev.key.code == sf::Keyboard::S)
			sPressed = true;
		if (ev.key.code == sf::Keyboard::D)
			dPressed = true;
	}
	if (ev.type == sf::Event::KeyReleased)
	{
		if (ev.key.code == sf::Keyboard::Q)
			qPressed = false;
		if (ev.key.code == sf::Keyboard::E)
			ePressed = false;
		if (ev.key.code == sf::Keyboard::W)
			wPressed = false;
		if (ev.key.code == sf::Keyboard::A)
			aPressed = false;
		if (ev.key.code == sf::Keyboard::S)
			sPressed = false;
		if (ev.key.code == sf::Keyboard::D)
			dPressed = false;
	}
}

void Application::update()
{
	if (zoomVel > 1.0f)
		zoomVel = 1.0f;
	if (zoomVel < -1.0f)
		zoomVel = -1.0f;
	zoom += zoomVel;
	zoomVel *= 0.9f;
	if (zoom < 0.2f)
	{
		zoom = 0.2f;
		zoomVel = 0.0f;
	}
	if (zoom > 1.7f)
	{
		zoom = 1.7f;
		zoomVel = 0.0f;
	}

	if (qPressed)
		spinVel -= 0.5f;
	if (ePressed)
		spinVel += 0.5f;
	spin += spinVel;
	spinVel *= 0.7f;

	if (wPressed)
		yVel += 2.0f;
	if (sPressed)
		yVel -= 2.0f;
	if (aPressed)
		xVel -= 2.0f;
	if (dPressed)
		xVel += 2.0f;
	x += xVel;
	y += yVel;
	xVel *= 0.85f;
	yVel *= 0.85f;

	camera.setYaw(spin);
	chunk.setScale(50.0f * zoom, 50.0f * zoom);
	chunk.setPosition(400.0f - x, 350.0f - y);
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