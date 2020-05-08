#include "State/PlayState.h"

#include <SFML/Graphics.hpp>

#include "Util/ColorShade.h"

PlayState::PlayState() :
	chunk(8, 9, 8)
{
	std::pair<CubeID, CubeTypeProperties> props[static_cast<int>(TestCubeType::COUNT)] =
	{
		std::make_pair(static_cast<CubeID>(TestCubeType::STONE), CubeTypeProperties(false)),
		std::make_pair(static_cast<CubeID>(TestCubeType::DIRT), CubeTypeProperties(false)),
		std::make_pair(static_cast<CubeID>(TestCubeType::GRASS), CubeTypeProperties(false)),
		std::make_pair(static_cast<CubeID>(TestCubeType::WATER), CubeTypeProperties(false)),
		std::make_pair(static_cast<CubeID>(TestCubeType::SAND), CubeTypeProperties(false)),
		std::make_pair(static_cast<CubeID>(TestCubeType::WOOD), CubeTypeProperties(false)),
		std::make_pair(static_cast<CubeID>(TestCubeType::LEAVES), CubeTypeProperties(true)),
	};
	chunk.addProperties(props, 7);
	for (int z = 0; z < 8; ++z)
	{
		for (int x = 0; x < 8; ++x)
		{
			chunk.setCube(x, 0, z, Cube(static_cast<CubeID>(TestCubeType::STONE)));
			chunk.setCube(x, 1, z, Cube(static_cast<CubeID>(TestCubeType::DIRT)));
			chunk.setCube(x, 2, z, Cube(static_cast<CubeID>(TestCubeType::GRASS)));
		}
	}
	chunk.setCube(1, 2, 1, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(2, 2, 1, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(3, 2, 1, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(4, 2, 1, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(1, 2, 2, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(1, 2, 3, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(1, 2, 4, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(2, 2, 4, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(3, 2, 4, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(4, 2, 4, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(4, 2, 3, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(4, 2, 2, Cube(static_cast<CubeID>(TestCubeType::SAND)));
	chunk.setCube(2, 2, 2, Cube(static_cast<CubeID>(TestCubeType::WATER)));
	chunk.setCube(2, 2, 3, Cube(static_cast<CubeID>(TestCubeType::WATER)));
	chunk.setCube(3, 2, 2, Cube(static_cast<CubeID>(TestCubeType::WATER)));
	chunk.setCube(3, 2, 3, Cube(static_cast<CubeID>(TestCubeType::WATER)));

	for (int y = 5; y < 5 + 3; ++y)
	{
		for (int z = 4; z < 4 + 3; ++z)
		{
			for (int x = 4; x < 4 + 3; ++x)
			{
				chunk.setCube(x, y, z, Cube(static_cast<CubeID>(TestCubeType::LEAVES)));
			}
		}
	}
	chunk.setCube(5, 8, 5, Cube(static_cast<CubeID>(TestCubeType::LEAVES)));
	chunk.setCube(5, 3, 5, Cube(static_cast<CubeID>(TestCubeType::WOOD)));
	chunk.setCube(5, 4, 5, Cube(static_cast<CubeID>(TestCubeType::WOOD)));
	chunk.setCube(5, 5, 5, Cube(static_cast<CubeID>(TestCubeType::WOOD)));
}

void PlayState::init()
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
	cubeSheet.add(static_cast<CubeID>(TestCubeType::STONE), mat);
	mat.indexX = 0;
	mat.indexY = 1;
	cubeSheet.add(static_cast<CubeID>(TestCubeType::DIRT), mat);
	mat.indexX = 0;
	mat.indexY = 2;
	cubeSheet.add(static_cast<CubeID>(TestCubeType::GRASS), mat);
	mat.indexX = 0;
	mat.indexY = 3;
	cubeSheet.add(static_cast<CubeID>(TestCubeType::WATER), mat);
	mat.indexX = 1;
	mat.indexY = 0;
	cubeSheet.add(static_cast<CubeID>(TestCubeType::SAND), mat);
	mat.indexX = 1;
	mat.indexY = 1;
	cubeSheet.add(static_cast<CubeID>(TestCubeType::WOOD), mat);
	mat.indexX = 1;
	mat.indexY = 2;
	cubeSheet.add(static_cast<CubeID>(TestCubeType::LEAVES), mat);
}

void PlayState::handleEvent(const sf::Event& ev)
{
}

void PlayState::update()
{
	camera.setPitch(30.0f);
	camera.rotateYaw(1.0f);
	chunk.setScale(50.0f, 50.0f);
	chunk.setPosition(400.0f, 350.0f);
	chunk.build(camera, cubeSheet);
}

void PlayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &cubeSheetTexture;
	target.draw(chunk, states);
}

void PlayState::enter()
{
}

void PlayState::exit()
{
}
