#ifndef APPLICATION_H
#define APPLICATION_H

#include "State/StateManager.h"
#include "State/StateType.h"

class Application
{
public:
	Application();

	void run();
private:
	StateManager stateManager;
};

#endif


