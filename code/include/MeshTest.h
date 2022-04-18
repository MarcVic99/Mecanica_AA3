#pragma once
#include <glm/glm.hpp>
#include "Simulator.h"
#include "VerlettIntegrator.h"
#include "Spring.h"

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
	~MeshTest();

	int GetIndex(int col, int row);

	void RenderUpdateMesh();

	void Update(float dt);

	int GetMaxMeshWidth(MeshTest mesh);

	int GetMaxMeshHeight(MeshTest mesh);

	void SetInitialMeshParticlePosition();

	int MeshTest::GetMaxMeshParticles();

private:
	int numParticles;

	glm::vec3* currentPositions;
	glm::vec3* currentVelocities;

	glm::vec3* previousPositions;
	glm::vec3* previousVelocities;

	glm::vec3* startingPositions;
	glm::vec3* startingVelocities;

	bool* isStatic;
	glm::vec3* forceAcumulator;

	const int particleMass = 1;

	VerlettIntegrator verletIntegrator;
	Spring* structuralSprings;
	Spring* shearSprings;
	Spring* bendingSprings;
};

