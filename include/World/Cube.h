#ifndef CUBE_H
#define CUBE_H

#include <cstdint>

typedef int8_t CubeID;

struct Cube
{
	Cube();
	Cube(CubeID id);
	CubeID id;
};

#endif