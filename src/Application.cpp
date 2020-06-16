#include "Application.h"

#include <utility>
#include <cmath>
#include <ctime>
#include <random>

#include "Util/ColorShade.h"
#include "Util/MathFunctions.h"

Application::Application() :
	frame(0),
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
	yVel(0.0f),

	width(1422),
	height(800),
	fps(60.0f)
{
	
	chunkGen(ChunkSize::SMALL);

	camera.setPitch(30.0f);
}

void Application::run()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Isometric Cubes");
	sf::View view;
	view.setSize(sf::Vector2f(width, -height));
	view.setCenter(width / 2.0f, height / 2.0f);
	window.setView(view);

	sf::Clock clock;
	sf::Time oldTime = clock.getElapsedTime();

	sf::Color clear(3, 64, 48);

	init();
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.getElapsedTime() - oldTime;
		oldTime = clock.getElapsedTime();
		delta = deltaTime.asSeconds();

		sf::Event ev;
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
			else
				handleEvent(ev);
		}
		update();

		window.clear(clear);
		window.draw(*this);
		window.display();
		++frame;
	}
}

void Application::init()
{
	cubeSheetTexture.loadFromFile("cubesheettemp.png");
	sf::Color col(255, 255, 255, 30);
	CubeMaterial waterMat =
	{
		0, 0, 16,
		col, col, col, col, col
	};
	CubeMaterial mat =
	{
		0, 0, 16,
		shaded(sf::Color::White, 1.0f),
		shaded(sf::Color::White, 0.7f),
		shaded(sf::Color::White, 0.5f),
		shaded(sf::Color::White, 0.3f),
		shaded(sf::Color::White, 0.5f)
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
	waterMat.indexX = 0;
	waterMat.indexY = 3;
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
	if (ev.type == sf::Event::MouseMoved)
	{
		camera.setPitch(ev.mouseMove.y / (float) height * 90.0f);
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
		if (ev.key.code == sf::Keyboard::Num1)
		{
			zeroVels();
			x = 0.0f;
			y = 0.0f;
			zoom = 0.3f;
			chunkGen(ChunkSize::SMALL);
		}
		if (ev.key.code == sf::Keyboard::Num2)
		{
			zeroVels();
			x = 0.0f;
			y = 0.0f;
			zoom = 0.17f;
			chunkGen(ChunkSize::MEDIUM);
		}
		if (ev.key.code == sf::Keyboard::Num3)
		{
			zeroVels();
			x = 0.0f;
			y = 0.0f;
			zoom = 0.12f;
			chunkGen(ChunkSize::LARGE);
		}
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
	zoom += zoomVel * fps * delta;
	zoomVel *= pow(0.9f, fps * delta);
	if (zoom < 0.1f)
	{
		zoom = 0.1f;
		zoomVel = 0.0f;
	}
	if (zoom > 1.7f)
	{
		zoom = 1.7f;
		zoomVel = 0.0f;
	}

	if (qPressed)
		spinVel -= 0.7f * fps * delta;
	if (ePressed)
		spinVel += 0.7f * fps * delta;
	spin += spinVel * fps * delta;
	spinVel *= pow(0.7f, fps * delta);

	if (wPressed)
		yVel += 3.0f * fps * delta;
	if (sPressed)
		yVel -= 3.0f * fps * delta;
	if (aPressed)
		xVel -= 3.0f * fps * delta;
	if (dPressed)
		xVel += 3.0f * fps * delta;
	x += xVel * fps * delta / zoom;
	y += yVel * fps * delta / zoom;
	xVel *= pow(0.85f, fps * delta);
	yVel *= pow(0.85f, fps * delta);

	float zoomScale = height / 12.0f;
	camera.setYaw(spin);
	chunk.setScale(zoomScale * zoom, zoomScale * zoom);
	chunk.setPosition(width / 2.0f - x * zoom, height / 2.0f - y * zoom);
	chunk.build(camera, cubeSheet);
}

void Application::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &cubeSheetTexture;
	target.draw(chunk, states);
}

void Application::chunkGen(ChunkSize size)
{
	int width = 0;
	int length = 0;
	int height = 38;
	switch (size)
	{
	case ChunkSize::SMALL:
		width = 30;
		length = 30;
		break;
	case ChunkSize::MEDIUM:
		width = 60;
		length = 60;
		break;
	case ChunkSize::LARGE:
		width = 90;
		length = 90;
		break;
	default:
		width = 30;
		length = 30;
	}

	noise = DistanceNoise(frame, 20.0f);
	chunk = CubeChunk(width, height, length);
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


	// Terrain
	int seaLevel = height / 2.3;
	for (int z = 0; z < length; ++z)
	{
		for (int x = 0; x < width; ++x)
		{
			int type = -1;
			int level = 0;
			int y = (int)(noise.sample(x, z) * height * 0.5f - height / 1.9f + noise.sample(-2 * x, -2 * z) * height * 0.15f + noise.sample(-0.5f * (x - 100), 0.5f * (z - 100)) * height * 1.3f);
			for (; y >= 0; --y)
			{
				if (level == 0)
					if (y <= seaLevel)
						type = 0;
					else
						type = 1;
				if (level > 5)
					chunk.setCube(x, y, z, Cube(cbID(Cubes::STONE)));
				else if (type == 0)
					chunk.setCube(x, y, z, Cube(cbID(Cubes::SAND)));
				else if (level == 0)
					chunk.setCube(x, y, z, Cube(cbID(Cubes::GRASS)));
				else
					chunk.setCube(x, y, z, Cube(cbID(Cubes::DIRT)));
				++level;
			}
		}
	}

	// Water
	for (int z = 0; z < length; ++z)
	{
		for (int x = 0; x < width; ++x)
		{
			int y = seaLevel;
			while (chunk.getCube(x, y, z).id == cbID(Cubes::EMPTY) && y >= 0)
			{
				chunk.setCube(x, y, z, Cube(cbID(Cubes::WATER)));
				y--;
			}
		}
	}

	// Trees
	int area = width * length;
	for (int i = 0; i < area / 330; ++i)
	{
		int x = rand() % width;
		int z = rand() % length;

		int y = height - 1;
		int grassY = 0;
		while (chunk.getCube(x, y, z).id == cbID(Cubes::EMPTY) && y >= 0)
			--y;
		grassY = y;
		if (chunk.getCube(x, y, z).id == cbID(Cubes::GRASS))
		{
			int treeHeight = 3 + rand() % 6;
			for (int t = 0; t < treeHeight; ++t)
			{
				chunk.setCube(x, ++y, z, Cube(cbID(Cubes::WOOD)));
			}

			int leavesStartY = grassY + 3 + rand() % (treeHeight - 2);
			int leavesR = 1 + rand() % 2;
			for (int lx = x - leavesR; lx <= x + leavesR; ++lx)
			{
				for (int lz = z - leavesR; lz <= z + leavesR; ++lz)
				{
					for (int ly = leavesStartY; ly <= grassY + treeHeight + 4; ++ly)
					{
						if (chunk.getCube(lx, ly, lz).id == cbID(Cubes::EMPTY))
							chunk.setCube(lx, ly, lz, cbID(Cubes::LEAVES));
					}
				}
			}
		}
	}
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

void Application::zeroVels()
{
	zoomVel = 0.0f;
	spinVel = 0.0f;
	xVel = 0.0f;
	yVel = 0.0f;
}
