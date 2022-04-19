#include "MeshTest.h"

MeshTest::MeshTest()
{
	numParticles = GetMaxMeshParticles();
	renderCloth = true;
	
	currentPositions = new glm::vec3[numParticles];
	currentVelocities = new glm::vec3[numParticles];

	startingPositions = new glm::vec3[numParticles];
	startingVelocities = new glm::vec3[numParticles];

	previousPositions = new glm::vec3[numParticles];
	previousVelocities = new glm::vec3[numParticles];

	startingPositions = new glm::vec3[numParticles];
	startingVelocities = new glm::vec3[numParticles];

	isStatic = new bool[numParticles];
	forceAcumulator = new glm::vec3[numParticles];

	for (int i = 0; i < numParticles; i++)
	{
		if (i == 0 || i == ClothMesh::numCols)
		{
			isStatic[i] = true;
		}
		else
		{
			isStatic[i] = false;
		}
	}
}

int MeshTest::GetIndex(int col, int row)
{
	return col + row * ClothMesh::numCols;
}

void MeshTest::Update(float dt)
{
	// Do verlett thingy
	for (int i = 0; i < numParticles; i++)
	{
		if (!isStatic[i])
		{
			currentVelocities[i] = verletIntegrator.GetAcceleration(forceAcumulator[i], particleMass);

			previousPositions[i] = currentPositions[i];
			currentPositions[i] = verletIntegrator.GetNewPosition(previousPositions[i], currentVelocities[i], dt);

			forceAcumulator[i] = { 0.f, 0.f, 0.f };
		}
	}
}

void MeshTest::RenderUpdateMesh()
{
	glm::vec3* positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];

	for (int row = 0; row < ClothMesh::numRows; row++)
	{
		for (int col = 0; col < ClothMesh::numCols; col++)
		{
			int indx = GetIndex(col, row);
			positions[indx] = glm::vec3(row - 5, col, 2.f);
		}
	}

	ClothMesh::updateClothMesh(&(positions[0].x));
}

MeshTest::~MeshTest()
{ 
	renderCloth = false; 
}

int MeshTest::GetMaxMeshParticles()
{
	return ClothMesh::numCols * ClothMesh::numRows;
}

void MeshTest::SetInitialMeshParticlePosition()
{
	
}
