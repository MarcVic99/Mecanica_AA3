#include "Spring.h"

glm::vec3 CalculateVectorBetweenTwoPointsSpring(glm::vec3 firstP, glm::vec3 secondP) {
	return firstP - secondP;
}

Spring::Spring(float* equilibriumD, float* K, float* D, int p1, int p2)
{
	equilibriumDistance = equilibriumD;
	constantK = K;
	dampingK = D;
	particle1 = p1;
	particle2 = p2;
}

Spring::~Spring()
{

}

glm::vec3 Spring::GetStrenghtBetweenTwoPositions(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 vel1, glm::vec3 vel2)
{
	glm::vec3 resultingStr = { 0.f, 0.f, 0.f };

	glm::vec3 vectorP2P1 = CalculateVectorBetweenTwoPointsSpring(pos1, pos2);
	glm::vec3 normalizedVectorP2P1 = glm::normalize(vectorP2P1);

	float damping = glm::dot(*dampingK * (vel1 - vel2), normalizedVectorP2P1);
	
	resultingStr = -(*constantK * (glm::length(vectorP2P1) - *equilibriumDistance) + damping) * normalizedVectorP2P1;

	return resultingStr;
}