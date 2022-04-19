#pragma once
#include <glm/glm.hpp>

class Spring
{
	Spring(float k, glm::vec3 equilDist);
	~Spring();

	glm::vec3 GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2);

	glm::vec3 equilibriumDistance;
	float constant;
	float damping;
};

