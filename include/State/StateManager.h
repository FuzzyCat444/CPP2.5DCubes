#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <string>
#include <unordered_map>
#include <utility>
#include <memory>

#include <SFML/Graphics.hpp>

#include "State/State.h"
#include "State/PlayState.h"

class StateManager
{
public:
	StateManager(int initialStateID);

	void addState(int stateID, std::unique_ptr<State>& state);

	void handleEvent(const sf::Event& ev);

	void update();

	void draw(sf::RenderTarget& target);

	void finishFrame();
private:
	std::unordered_map<int, std::unique_ptr<State>> stateMap;
	int currentStateID;
};

#endif