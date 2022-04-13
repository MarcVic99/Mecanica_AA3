#pragma once
#include <glm/glm.hpp>
#include "Simulator.h"

extern bool renderCloth;

namespace ClothMesh
{
	extern void updateClothMesh(float* aray_data);
	extern const int numCols;
	extern const int numRows;
}

class MeshTest
{
public:
	MeshTest();

	int GetIndex(int col, int row);
	
	void RenderUpdateMesh();

	~MeshTest();

	void Update(float dt);

	int GetMaxMeshWidth(MeshTest mesh);

	int GetMaxMeshHeight(MeshTest mesh);

	void SetInitialMeshParticlePosition();

	int MeshTest::GetMaxMeshParticles();

private:

	glm::vec3* currentPositions;
	glm::vec3* currentVelocities;

	glm::vec3* previousPositions;
	glm::vec3* previousVelocities;

	glm::vec3* startingPositions;
	glm::vec3* startingVelocities;

	int particleMass = 1;


};

