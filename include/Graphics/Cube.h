#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>

struct CubeMaterial
{
	CubeMaterial(float size, const sf::Texture* netTex, sf::Color topShade, sf::Color frontShade, sf::Color leftShade, sf::Color backShade, sf::Color rightShade);

	float size;
	const sf::Texture* netTex;
	sf::Color topShade;
	sf::Color frontShade;
	sf::Color leftShade;
	sf::Color backShade;
	sf::Color rightShade;
};

struct CubeOrientation
{
	CubeOrientation(float yaw, float pitch);

	float yaw;
	float cosYaw, sinYaw;
	float cosPitch, sinPitch;
};

class Cube : public sf::Drawable
{
public:
	Cube(const CubeMaterial& material, const CubeOrientation& orientation);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void init(const CubeMaterial& material, const CubeOrientation& orientation);

	struct CubeSide
	{
		sf::Sprite sprite;
		sf::Color shade;
		sf::Transform transform;
	}
	top,
	left,
	right;
};

#endif