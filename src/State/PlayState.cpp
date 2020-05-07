#include "State/PlayState.h"

#include <SFML/Graphics.hpp>

#include "Util/ColorShade.h"

PlayState::PlayState() :
	chunk(6, 6, 6)
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
	for (int z = 0; z < 6; ++z)
	{
		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 6; ++x)
			{
				chunk.setCube(x, y, z, x * y % static_cast<int>(TestCubeType::COUNT));
			}
		}
	}
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
	chunk.setPosition(400.0f, 300.0f);
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
