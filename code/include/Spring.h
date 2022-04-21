#pragma once
#include <glm/glm.hpp>

class Spring
{
public:
	Spring(float k, float damp, glm::vec3 equilDist);
	~Spring();

	glm::vec3 GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2);

	int idx1;
	int idx2;

	glm::vec3 equilibriumDistance;
	float constant;
	float damping;
	//float longitude;

	enum SpringType
	{
		BENDING,
		STRETCH,
	};

};

