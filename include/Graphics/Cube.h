#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>

struct CubeMaterial
{
	CubeMaterial(float size, const sf::Texture* top, sf::Color topShade,
							 const sf::Texture* front, sf::Color frontShade,
							 const sf::Texture* left, sf::Color leftShade,
							 const sf::Texture* back, sf::Color backShade,
							 const sf::Texture* right, sf::Color rightShade);

	float size;
	const sf::Texture* topTex;
	sf::Color topShade;
	const sf::Texture* frontTex;
	sf::Color frontShade;
	const sf::Texture* leftTex;
	sf::Color leftShade;
	const sf::Texture* backTex;
	sf::Color backShade;
	const sf::Texture* rightTex;
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
	void buildVertices(const CubeMaterial& material, const CubeOrientation& orientation);

	sf::VertexArray cubeVertexArr;
};

#endif