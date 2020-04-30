#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class StateManager;

class State : sf::Drawable
{
public:
	State();

	virtual void init() = 0;

	virtual void handleEvent(const sf::Event& ev) = 0;

	virtual void update() = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual void enter() = 0;

	virtual void exit() = 0;
protected:
	void switchToState(int stateID)
	{
		doSwitch = true;
		nextStateID = stateID;
	}
private:
	bool doSwitch;
	int nextStateID;

	friend StateManager;
};

#endif

