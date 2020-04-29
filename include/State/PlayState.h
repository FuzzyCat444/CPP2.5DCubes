#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State/State.h"
#include "State/StateType.h"

class PlayState : public State
{
	void handleEvent(const sf::Event& ev) override;

	void update() override;

	void draw(sf::RenderTarget& target) override;

	void enter() override;

	void exit() override;
};

#endif