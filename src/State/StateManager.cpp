#include "State/StateManager.h"

StateManager::StateManager(int initialStateID) : currentStateID(initialStateID)
{
	
}

void StateManager::addState(int stateID, std::unique_ptr<State>& state)
{
	stateMap[stateID] = std::move(state);
}

void StateManager::handleEvent(const sf::Event& ev)
{
	stateMap[currentStateID]->handleEvent(ev);
}

void StateManager::update()
{
	stateMap[currentStateID]->update();
}

void StateManager::draw(sf::RenderTarget& target)
{
	stateMap[currentStateID]->draw(target);
}

void StateManager::finishFrame()
{
	State& prevState = *stateMap[currentStateID];
	if (prevState.doSwitch)
	{
		prevState.doSwitch = false;
		currentStateID = prevState.nextStateID;
		prevState.exit();
		stateMap[currentStateID]->enter();
	}
}