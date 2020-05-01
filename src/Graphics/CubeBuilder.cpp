#include "Graphics/CubeBuilder.h"

#include <cmath>

#include "Util/MathFunctions.h"

/*

CubeBuilder

*/

CubeBuilder::CubeBuilder() :
	vertices(sf::Quads)
{
}

CubeBuilder::~CubeBuilder()
{
}

void CubeBuilder::draw(sf::RenderTarget& target, sf::RenderStates renderStates) const
{
	renderStates.transform *= getTransform();
	target.draw(vertices, renderStates);
}

void CubeBuilder::putCube(CubeVisual& cubeVisual)
{
	const sf::VertexArray& cubeVerts = cubeVisual.getTransformedVertices();
	for (int i = 0; i < cubeVerts.getVertexCount(); ++i)
	{
		vertices.append(cubeVerts[i]);
	}
}

void CubeBuilder::clear()
{
	vertices.clear();
}

/*

CubeMaterial

*/

CubeMaterial::CubeMaterial(int indexX, int indexY, int size, sf::Color topShade, sf::Color frontShade, sf::Color leftShade, sf::Color backShade, sf::Color rightShade) :
	indexX(indexX), indexY(indexY), size(size), topShade(topShade), frontShade(frontShade), leftShade(leftShade), backShade(backShade), rightShade(rightShade)
{
}

/*

CubeOrientation

*/

CubeOrientation::CubeOrientation(float yaw, float pitch) :
	yaw(std::fmod(yaw, 360.0f)),
	cosYaw(std::cos(rads(yaw))), sinYaw(std::sin(rads(yaw))),
	cosYawMod90(std::cos(rads(std::fmod(yaw, 90.0f)))), sinYawMod90(std::sin(rads(std::fmod(yaw, 90.0f)))),
	cosPitch(std::cos(rads(pitch))), sinPitch(std::sin(rads(pitch)))
{
}

/*

CubeVisual

*/

CubeVisual::CubeVisual(const CubeMaterial& material, const CubeOrientation& orientation) :
	vertices(), transformedVertices()
{
	set(material, orientation);
}

void CubeVisual::set(const CubeMaterial& material, const CubeOrientation& orientation)
{
	vertices.clear();

	float sideW = 1.0f;
	float halfSideW = sideW / 2.0f;

	float b = sideW * orientation.cosPitch;
	float l = sideW * orientation.sinYawMod90;
	float r = sideW * orientation.cosYawMod90;
	float tu = r * orientation.sinPitch;
	float tl = l * orientation.sinPitch;
	float t = tu + tl;
	float b2 = b / 2.0f;
	float t2 = t / 2.0f;

	sf::Vector2f startTexCoords(material.indexX * material.size * 5, material.indexY * material.size);
	sf::Vector2f texSizeX(material.size, 0.0f);
	sf::Vector2f texSizeY(0.0f, material.size);

	sf::Vector2f tp0(halfSideW * (orientation.cosYaw - orientation.sinYaw), halfSideW * (orientation.cosYaw + orientation.sinYaw));
	sf::Vector2f tp1(-tp0.y, tp0.x);
	sf::Vector2f tp2(-tp1.y, tp1.x);
	sf::Vector2f tp3(-tp2.y, tp2.x);
	float tScale = orientation.sinPitch;
	tp0 = sf::Vector2f(tp0.x, tp0.y * tScale + b2);
	tp1 = sf::Vector2f(tp1.x, tp1.y * tScale + b2);
	tp2 = sf::Vector2f(tp2.x, tp2.y * tScale + b2);
	tp3 = sf::Vector2f(tp3.x, tp3.y * tScale + b2);
	vertices.append(sf::Vertex(tp0, material.topShade, startTexCoords + texSizeX));
	vertices.append(sf::Vertex(tp1, material.topShade, startTexCoords));
	vertices.append(sf::Vertex(tp2, material.topShade, startTexCoords + texSizeY));
	vertices.append(sf::Vertex(tp3, material.topShade, startTexCoords + texSizeX + texSizeY));
}

const sf::VertexArray& CubeVisual::getTransformedVertices()
{
	transformedVertices.clear();
	for (int i = 0; i < vertices.getVertexCount(); ++i)
	{
		const sf::Vertex& orig = vertices[i];
		transformedVertices.append(sf::Vertex(getTransform().transformPoint(orig.position), orig.color, orig.texCoords));
	}
	return transformedVertices;
}
