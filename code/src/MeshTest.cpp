#include "MeshTest.h"

MeshTest::MeshTest()
{
	renderCloth = true;
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
		if (!meshParticle[i].isStatic)
		{
			meshParticle[i].currentVelocities[i] = verletIntegrator.GetAcceleration(meshParticle[i].forceAcumulator[i], meshParticle[i].particleMass);

			meshParticle[i].previousPositions[i] = meshParticle[i].currentPositions[i];
			meshParticle[i].currentPositions[i] = verletIntegrator.GetNewPosition(meshParticle[i].previousPositions[i], meshParticle[i].currentVelocities[i], dt);

			meshParticle[i].forceAcumulator[i] = { 0.f, 0.f, 0.f };
		}
	}

	//for(int i = 0; i<steps; i++)
	//{
			//Mesh.Update(dt/steps);
	//}
	//Mesh.Render();
}

void MeshTest::RenderUpdateMesh()
{
	glm::vec3* positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];

	for (int row = 0; row < ClothMesh::numRows; row++)
	{
		for (int col = 0; col < ClothMesh::numCols; col++)
		{
			int indx = GetIndex(col, row);
			positions[indx] = glm::vec3(row - 5, 10, col -5);
			meshParticle[indx].currentPositions[indx] = positions[indx];
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
