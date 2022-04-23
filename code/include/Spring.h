#pragma once
#include <glm/glm.hpp>

class Spring
{
public:
	Spring();
	~Spring();

	glm::vec3 GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 vel1, glm::vec3 vel2);
	int particle1;
	int particle2;

	float equilibriumDistance;
	float constantK;
	float dampingK;
};

