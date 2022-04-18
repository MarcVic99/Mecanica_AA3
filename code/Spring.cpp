#include "Spring.h"

Spring::Spring(float k, glm::vec3 equilDist)
{
	constant = k;
	equilibriumDistance = equilDist;
}

Spring::~Spring()
{

}

glm::vec3 Spring::GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2)
{
	glm::vec3 resultingStr = { 0,0,0 };

	resultingStr = -constant * (equilibriumDistance - (pos1 - pos2));

	return resultingStr;
}