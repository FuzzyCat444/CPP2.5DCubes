#include "Util/ColorShade.h"

#include <cmath>

sf::Color shaded(sf::Color color, float amt)
{
	int r = std::lround(color.r * amt);
	int g = std::lround(color.g * amt);
	int b = std::lround(color.b * amt);
	return sf::Color(r, g, b);
}
