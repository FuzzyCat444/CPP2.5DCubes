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

void Camera::computeForwardVec()
{
	float yawRad = rads(yaw);
	float pitchRad = rads(pitch);
	sf::Vector3f forward(0.0f, 0.0f, 0.0f);

	float cosPitch = std::cos(pitchRad);
	forward.y = -std::sin(pitchRad);
	forward.x = -std::sin(yawRad) * cosPitch;
	forward.z = std::cos(yawRad) * cosPitch;
}
