#include <memory>
#include "Application.h"

int main(int arc, char* argv[]) 
{
	auto app = std::make_unique<Application>();
	app->run();
}