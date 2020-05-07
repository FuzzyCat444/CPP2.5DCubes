#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State/State.h"
#include "State/StateType.h"
#include "Graphics/CubeBuilder.h"
#include "Graphics/CubeSheet.h"
#include "Graphics/Camera.h"
#include "World/CubeChunk.h"
#include "World/Cube.h"

class PlayState : public State
{
public:
	PlayState();

	void init() override;

	void handleEvent(const sf::Event& ev) override;

	void update() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void enter() override;

	void exit() override;
private:
	enum class TestCubeType : CubeID
	{
		EMPTY = -1,
		STONE = 0,
		DIRT = 1,
		GRASS = 2,
		WATER = 3,
		SAND = 4,
		WOOD = 5,
		LEAVES = 6,
		COUNT
	};

	sf::Texture cubeSheetTexture;
	Camera camera;
	CubeSheet cubeSheet;
	CubeChunk chunk;
};

#endif