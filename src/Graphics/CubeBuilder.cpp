#include "Graphics/CubeBuilder.h"

#include <cmath>

#include "Util/MathFunctions.h"

/*

CubeBuilder

*/
CubeBuilder::CubeBuilder() :
	vertices()
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

/*

CubeMaterial

*/

CubeMaterial::CubeMaterial(int indexX, int indexY, int size) :
	indexX(indexX), indexY(indexY), size(size)
{
}

/*

CubeOrientation

*/

CubeOrientation::CubeOrientation(float yaw, float pitch) :
	yaw(std::fmod(yaw, 360.0f)),
	cosYaw(std::cos(rads(std::fmod(yaw, 90.0f)))), sinYaw(std::sin(rads(std::fmod(yaw, 90.0f)))),
	cosPitch(std::cos(rads(pitch))), sinPitch(std::sin(rads(pitch)))
{
}

/*

CubeVisual

*/

CubeVisual::CubeVisual(const CubeMaterial& material, const CubeOrientation& orientation) :
	vertices(), transformedVertices()
{

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
