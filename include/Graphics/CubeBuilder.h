#ifndef CUBEBUILDER_H
#define CUBEBUILDER_H

#include <SFML/Graphics.hpp>

struct CubeMaterial
{
	CubeMaterial(int indexX, int indexY, int size);
	int indexX;
	int indexY;
	int size;
};

struct CubeOrientation
{
	CubeOrientation(float yaw, float pitch);
	float yaw;
	float cosYaw, sinYaw;
	float cosPitch, sinPitch;
};

class CubeVisual : public sf::Transformable
{
public:
	CubeVisual(const CubeMaterial& material, const CubeOrientation& orientation);

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
private:
	sf::VertexArray vertices;
};

#endif

