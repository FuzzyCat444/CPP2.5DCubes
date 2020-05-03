#include "World/Cube.h"

Cube::Cube() :
	Cube(0)
{
}

Cube::Cube(CubeID id) :
	id(id), neighborFlags(0)
{
}
