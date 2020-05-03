#ifndef CUBEBUILDER_H
#define CUBEBUILDER_H

#include <SFML/Graphics.hpp>

struct CubeMaterial
{
	CubeMaterial(int indexX, int indexY, int size, sf::Color topShade, sf::Color frontShade, sf::Color leftShade, sf::Color backShade, sf::Color rightShade);
	int indexX;
	int indexY;
	int size;
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
	float cosYawMod90, sinYawMod90;
	float cosPitch, sinPitch;
};

class CubeVisual : public sf::Transformable
{
public:
	CubeVisual(const CubeMaterial& material, const CubeOrientation& orientation);
	void set(const CubeMaterial& material, const CubeOrientation& orientation);

	const sf::VertexArray& getTransformedVertices();
private:
	sf::VertexArray vertices;
	sf::VertexArray transformedVertices;
};

class CubeBuilder : public sf::Drawable, public sf::Transformable
{
public:
	CubeBuilder();
	~CubeBuilder();

	void draw(sf::RenderTarget& target, sf::RenderStates renderStates) const override;

	void putCube(CubeVisual& cubeVisual);

	void clear();
private:
	sf::VertexArray vertices;
};

#endif

