#include "Util/MathFunctions.h"

const double PI = 3.14159265358979323;

double rads(double degs)
{
	return degs * PI / 180.0;
}

double degs(double rads)
{
	return rads * 180.0 / PI;
}