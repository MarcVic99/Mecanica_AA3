#pragma once
#include <glm/glm.hpp>
#include "Simulator.h"
#include "Spring.h"
#include "MeshParticles.h"

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

	void SetInitialMeshPosition();
	void SetInitialMeshParticlePositionAndVelocity();

	int GetNumMeshParticles();
	int GetNumCols();
	int GetNumRows();

	glm::vec3* positions;
	glm::vec3* forceAcumulator;
	//int numParticles;

	MeshParticles* meshParticles;

	// VerlettIntegrator* verletIntegrator;
	//Spring* structuralSprings;
	//Spring* shearSprings;
	//Spring* bendingSprings;
};

