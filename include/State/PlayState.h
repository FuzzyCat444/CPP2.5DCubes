#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State/State.h"
#include "State/StateType.h"
#include "Graphics/Cube.h"

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
	sf::Texture furnace;
	Cube cube;
};

#endif