#include "Graphics/Cube.h"

#include <cmath>

#include "Util/MathFunctions.h"

Cube::Cube(const CubeMaterial& material, const CubeOrientation& orientation)
{
	buildVertices(material, orientation);
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(cubeVertexArr);
}

void Cube::buildVertices(const CubeMaterial& material, const CubeOrientation& orientation)
{
	const sf::Texture* topTex = material.topTex;
	const sf::Texture* leftTex = nullptr;
	const sf::Texture* rightTex = nullptr;

	sf::Color topShade = material.topShade;
	sf::Color leftShade;
	sf::Color rightShade;

	if (orientation.yaw < 90.0f)
	{
		leftTex = material.rightTex; leftShade = material.rightShade;
		rightTex = material.frontTex; rightShade = material.frontShade;
	}
	else if (orientation.yaw < 180.0f)
	{
		leftTex = material.backTex; leftShade = material.backShade;
		rightTex = material.rightTex; rightShade = material.rightShade;
	}
	else if (orientation.yaw < 270.0f)
	{
		leftTex = material.leftTex; leftShade = material.leftShade;
		rightTex = material.backTex; rightShade = material.backShade;
	}
	else
	{
		leftTex = material.frontTex; leftShade = material.frontShade;
		rightTex = material.leftTex; rightShade = material.leftShade;
	}

	float tu = material.size * orientation.cosYaw * orientation.sinPitch;
	float tl = material.size * orientation.sinYaw * orientation.sinPitch;
	float t = tu + tl;
	float b = material.size * orientation.cosPitch;
	float l = material.size * orientation.sinYaw;
	float r = material.size * orientation.cosYaw;
}

CubeMaterial::CubeMaterial(float size, const sf::Texture* topTex, sf::Color topShade, 
									   const sf::Texture* frontTex, sf::Color frontShade, 
									   const sf::Texture* leftTex, sf::Color leftShade, 
									   const sf::Texture* backTex, sf::Color backShade, 
									   const sf::Texture* rightTex, sf::Color rightShade) :
	size(size),
	topTex(topTex), topShade(topShade),
	frontTex(frontTex), frontShade(frontShade),
	leftTex(leftTex), leftShade(leftShade),
	backTex(backTex), backShade(backShade),
	rightTex(rightTex), rightShade(rightShade)
{
}

CubeOrientation::CubeOrientation(float yaw, float pitch) :
	yaw(std::fmod(360.0f + std::fmod(yaw, 360.0f), 360.0f))
{
	float mYaw = std::fmod(yaw, 90.0f);
	float cosYaw = std::cos(rads(mYaw));
	float sinYaw = std::sin(rads(mYaw));
	float cosPitch = std::cos(rads(pitch));
	float sinPitch = std::sin(rads(pitch));

	this->cosYaw = cosYaw;
	this->sinYaw = sinYaw;
	this->cosPitch = cosPitch;
	this->sinPitch = sinPitch;
}
