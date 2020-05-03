#include "State/StateManager.h"

StateManager::StateManager(int initialStateID) : currentStateID(initialStateID)
{
	
}

void StateManager::addState(int stateID, std::unique_ptr<State>& state)
{
	stateMap.insert(std::make_pair(stateID, std::move(state)));
}

void StateManager::init()
{
	for (auto it = stateMap.begin(); it != stateMap.end(); ++it)
	{
		it->second->init();
	}
	stateMap.at(currentStateID)->enter();
}

void StateManager::handleEvent(const sf::Event& ev)
{
	stateMap.at(currentStateID)->handleEvent(ev);
}

void StateManager::update()
{
	stateMap.at(currentStateID)->update();
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	stateMap.at(currentStateID)->draw(target, states);
}

void StateManager::finishFrame()
{
	State& prevState = *stateMap.at(currentStateID);
	if (prevState.doSwitch)
	{
		prevState.doSwitch = false;
		currentStateID = prevState.nextStateID;
		prevState.exit();
		stateMap.at(currentStateID)->enter();
	}
}