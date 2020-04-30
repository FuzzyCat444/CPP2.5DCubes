#include "Graphics/Cube.h"

#include <cmath>
#include <vector>

#include "Util/MathFunctions.h"

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

void Cube::init(const CubeMaterial& material, const CubeOrientation& orientation)
{
	sf::IntRect topRect(0 * material.size, 0, material.size, material.size);
	sf::IntRect frontRect(1 * material.size, 0, material.size, material.size);
	sf::IntRect leftRect(2 * material.size, 0, material.size, material.size);
	sf::IntRect backRect(3 * material.size, 0, material.size, material.size);
	sf::IntRect rightRect(4 * material.size, 0, material.size, material.size);

	CubeSide topSide;
	CubeSide leftSide;
	CubeSide rightSide;

	if (orientation.yaw < 90.0f)
	{
		leftSide.shade = material.rightShade; leftSide.sprite = sf::Sprite(*material.netTex, rightRect);
		rightSide.shade = material.frontShade; rightSide.sprite = sf::Sprite(*material.netTex, frontRect);
	}
	else if (orientation.yaw < 180.0f)
	{
		leftSide.shade = material.backShade; leftSide.sprite = sf::Sprite(*material.netTex, backRect);
		rightSide.shade = material.rightShade; rightSide.sprite = sf::Sprite(*material.netTex, rightRect);
	}
	else if (orientation.yaw < 270.0f)
	{
		leftSide.shade = material.leftShade; leftSide.sprite = sf::Sprite(*material.netTex, leftRect);
		rightSide.shade = material.backShade; rightSide.sprite = sf::Sprite(*material.netTex, backRect);
	}
	else
	{
		leftSide.shade = material.frontShade; leftSide.sprite = sf::Sprite(*material.netTex, frontRect);
		rightSide.shade = material.leftShade; rightSide.sprite = sf::Sprite(*material.netTex, leftRect);
	}

	float tu = material.size * orientation.cosYaw * orientation.sinPitch;
	float tl = material.size * orientation.sinYaw * orientation.sinPitch;
	float t = tu + tl;
	float b = material.size * orientation.cosPitch;
	float l = material.size * orientation.sinYaw;
	float r = material.size * orientation.cosYaw;

	float halfSize = material.size / 2.0f;

	sf::Transform tr;

	// Top
	std::vector<sf::Vector2f> topPoints
	{
		sf::Vector2f(-halfSize, -halfSize),
		sf::Vector2f(halfSize, -halfSize),
		sf::Vector2f(halfSize, halfSize),
		sf::Vector2f(-halfSize, halfSize)
	};

	tr = sf::Transform::Identity;
	tr.rotate(orientation.yaw).scale(sf::Vector2f(1.0f, orientation.sinPitch)).translate(sf::Vector2f(0.0f, b / 2.0f));
	for (auto it = topPoints.begin(); it != topPoints.end; ++it) {
		
	}
}

CubeMaterial::CubeMaterial(float size, const sf::Texture* netTex, sf::Color topShade, sf::Color frontShade, sf::Color leftShade, sf::Color backShade, sf::Color rightShade) :
	size(size), netTex(netTex), topShade(topShade), frontShade(frontShade), leftShade(leftShade), backShade(backShade), rightShade(rightShade)
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
