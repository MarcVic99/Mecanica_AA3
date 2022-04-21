#include "Spring.h"

Spring::Spring()
{
	
}

Spring::~Spring()
{

}

glm::vec3 Spring::GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 vel1, glm::vec3 vel2)
{
	glm::vec3 resultingStr = { 0.f, 0.f, 0.f };

	resultingStr = -(constantK * (glm::mod(pos1, pos2) - equilibriumDistance) + 
		damping * (vel1 - vel2) * (pos1 - pos2) / (glm::mod(pos1, pos2))) 
		* (pos1 - pos2) / (glm::mod(pos1, pos2));

	return resultingStr;
}