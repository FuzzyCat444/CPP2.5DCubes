#ifndef CUBE_H
#define CUBE_H

#include <cstdint>

typedef uint8_t CubeID;

struct Cube
{
	Cube();
	Cube(CubeID id);
	CubeID id;
	uint8_t neighborFlags;
};

#endif