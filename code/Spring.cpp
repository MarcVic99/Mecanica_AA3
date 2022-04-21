#include "Spring.h"

Spring::Spring(float k, float damp, glm::vec3 equilDist)
{
	constant = k;
	damping = damp;
	equilibriumDistance = equilDist;
}

Spring::~Spring()
{

}

glm::vec3 Spring::GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2)
{
	glm::vec3 resultingStr = { 0.f, 0.f, 0.f };

	resultingStr = -constant * (equilibriumDistance - (pos1 - pos2));

	return resultingStr;
}