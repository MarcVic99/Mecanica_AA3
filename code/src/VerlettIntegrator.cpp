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

glm::vec3 VerlettIntegrator::GetNewPosition(glm::vec3 lastPos, glm::vec3 accel, float dt)
{
	return lastPos + accel * dt * dt;
}
