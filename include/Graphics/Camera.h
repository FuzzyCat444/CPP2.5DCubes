#ifndef CAMERA_H
#define CAMERA_H

#include <array>

#include <SFML/Graphics.hpp>

#include "Graphics/CubeBuilder.h"

class Camera
{
public:
	Camera();

	void setYaw(float yawAngle);
	void setPitch(float pitchAngle);
	void set(float yawAngle, float pitchAngle);
	void rotateYaw(float yawAngle);
	void rotatePitch(float pitchAngle);
	void rotate(float yawAngle, float pitchAngle);

	float depthOf(sf::Vector3f pt) const;

	CubeOrientation getCubeOrientation() const;
	std::array<sf::Vector2f, 3> getOrientationVectors() const;
private:
	void computeForwardVec();

	float yaw;
	float pitch;
	sf::Vector3f forwardVec;
};

#endif