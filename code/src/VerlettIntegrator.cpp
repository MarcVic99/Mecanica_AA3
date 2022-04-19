#include "VerlettIntegrator.h"

VerlettIntegrator::VerlettIntegrator()
{
}

VerlettIntegrator::~VerlettIntegrator()
{
}

glm::vec3 VerlettIntegrator::GetAcceleration(glm::vec3 forceAcum, float mass)
{
	return forceAcum / mass;
}

glm::vec3 VerlettIntegrator::GetNewPosition(glm::vec3 currPos, glm::vec3 lastPos, glm::vec3 accel, float dt)
{
	return currPos + (currPos - lastPos) + accel * dt * dt;
}

glm::vec3 VerlettIntegrator::GetNewVelocity(glm::vec3 newPos, glm::vec3 currPos, float dt)
{
	return (newPos - currPos) / dt;
}
