#include "Graphics/Camera.h"

#include <cmath>

#include "Util/MathFunctions.h"

Camera::Camera()
{
	set(0.0f, 0.0f);
}

void Camera::setYaw(float yawAngle)
{
	set(yawAngle, pitch);
}

void Camera::setPitch(float pitchAngle)
{
	set(yaw, pitchAngle);
}

void Camera::set(float yawAngle, float pitchAngle)
{
	yaw = yawAngle;
	pitch = pitchAngle;
	pitch = std::fmaxf(0.0f, std::fminf(90.0f, pitch));
	computeForwardVec();
}

void Camera::rotateYaw(float yawAngle)
{
	rotate(yawAngle, 0.0f);
}

void Camera::rotatePitch(float pitchAngle)
{
	rotate(0.0f, pitchAngle);
}

void Camera::rotate(float yawAngle, float pitchAngle)
{
	yaw += yawAngle;
	pitch += pitchAngle;
	pitch = std::fmaxf(0.0f, std::fminf(90.0f, pitch));
	computeForwardVec();
}

float Camera::depthOf(sf::Vector3f pt) const
{
	return pt.x * forwardVec.x + pt.y * forwardVec.y + pt.z * forwardVec.z;
}

CubeOrientation Camera::getCubeOrientation() const
{
	return CubeOrientation(-yaw, pitch);
}

std::array<sf::Vector2f, 3> Camera::getOrientationVectors() const
{
	std::array<sf::Vector2f, 3> vecs;

	float yawRad = rads(yaw);
	float pitchRad = rads(pitch);

	float cosYaw = std::cos(-yawRad);
	float sinYaw = std::sin(-yawRad);
	float cosPitch = std::cos(pitchRad);
	float sinPitch = std::sin(pitchRad);

	vecs[0] = sf::Vector2f(cosYaw, sinYaw * sinPitch);  // X (right)
	vecs[1] = sf::Vector2f(0.0f, 1.0f * cosPitch);      // Y (up)
	vecs[2] = sf::Vector2f(-sinYaw, cosYaw * sinPitch); // Z (forward)

	return vecs;
}

void Camera::computeForwardVec()
{
	float yawRad = rads(yaw);
	float pitchRad = rads(pitch);

	float cosPitch = std::cos(pitchRad);
	forwardVec.y = -std::sin(pitchRad);
	forwardVec.x = -std::sin(yawRad) * cosPitch;
	forwardVec.z = std::cos(yawRad) * cosPitch;
}
