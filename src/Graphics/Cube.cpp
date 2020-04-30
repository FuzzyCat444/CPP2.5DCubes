#include "Graphics/Cube.h"

#include <cmath>
#include <vector>

#include "Util/MathFunctions.h"

Cube::Cube()
{
}

Cube::Cube(const CubeMaterial& material, const CubeOrientation& orientation)
{
	init(material, orientation);
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= top.transform;
	target.draw(top.sprite, states);
}

void Cube::init(const CubeMaterial& material, const CubeOrientation& orientation)
{
	sf::IntRect topRect(0 * material.size, 0, material.size, material.size);
	sf::IntRect frontRect(1 * material.size, 0, material.size, material.size);
	sf::IntRect leftRect(2 * material.size, 0, material.size, material.size);
	sf::IntRect backRect(3 * material.size, 0, material.size, material.size);
	sf::IntRect rightRect(4 * material.size, 0, material.size, material.size);

	if (orientation.yaw < 90.0f)
	{
		left.shade = material.rightShade; left.sprite = sf::Sprite(*material.netTex, rightRect);
		right.shade = material.frontShade; right.sprite = sf::Sprite(*material.netTex, frontRect);
	}
	else if (orientation.yaw < 180.0f)
	{
		left.shade = material.backShade; left.sprite = sf::Sprite(*material.netTex, backRect);
		right.shade = material.rightShade; right.sprite = sf::Sprite(*material.netTex, rightRect);
	}
	else if (orientation.yaw < 270.0f)
	{
		left.shade = material.leftShade; left.sprite = sf::Sprite(*material.netTex, leftRect);
		right.shade = material.backShade; right.sprite = sf::Sprite(*material.netTex, backRect);
	}
	else
	{
		left.shade = material.frontShade; left.sprite = sf::Sprite(*material.netTex, frontRect);
		right.shade = material.leftShade; right.sprite = sf::Sprite(*material.netTex, leftRect);
	}
	top.shade = material.topShade; top.sprite = sf::Sprite(*material.netTex, topRect);

	float tu = material.size * orientation.cosYaw * orientation.sinPitch;
	float tl = material.size * orientation.sinYaw * orientation.sinPitch;
	float t = tu + tl;
	float b = material.size * orientation.cosPitch;
	float l = material.size * orientation.sinYaw;
	float r = material.size * orientation.cosYaw;

	float halfSize = material.size / 2.0f;

	// Top
	std::vector<sf::Vector2f> topPoints
	{
		sf::Vector2f(-halfSize, -halfSize),
		sf::Vector2f(halfSize, -halfSize),
		sf::Vector2f(halfSize, halfSize),
		sf::Vector2f(-halfSize, halfSize)
	};

	top.sprite.setOrigin(halfSize, halfSize);
	top.transform.translate(sf::Vector2f(0.0f, b / 2.0f)).scale(sf::Vector2f(1.0f, orientation.sinPitch)).rotate(orientation.yaw);
}

CubeMaterial::CubeMaterial() :
	CubeMaterial(0, nullptr, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White, sf::Color::White)
{
}

CubeMaterial::CubeMaterial(float size, const sf::Texture* netTex, sf::Color topShade, sf::Color frontShade, sf::Color leftShade, sf::Color backShade, sf::Color rightShade) :
	size(size), netTex(netTex), topShade(topShade), frontShade(frontShade), leftShade(leftShade), backShade(backShade), rightShade(rightShade)
{
}

CubeOrientation::CubeOrientation() :
	CubeOrientation(0.0f, 0.0f)
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
