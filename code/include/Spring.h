#pragma once
#include <glm/glm.hpp>

class Spring
{
public:
	Spring();
	~Spring();

	glm::vec3 GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 vel1, glm::vec3 vel2);

	int idx1;
	int idx2;

	float equilibriumDistance = 1.f;
	const float constantK = 5.f;
	const float damping = 5.f;
	//float longitude;

	enum SpringType
	{
		STRUCTURAL,
		BENDING,
		STRETCH,
	};

};

