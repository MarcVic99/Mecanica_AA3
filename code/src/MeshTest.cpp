#include "MeshTest.h"

MeshTest::MeshTest()
{
	renderCloth = true;
	
	positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
	SetInitialMeshPosition();

	meshParticles = new MeshParticles(ClothMesh::numCols * ClothMesh::numRows);
	SetInitialMeshParticlePosition();
}

MeshTest::~MeshTest()
{
	delete meshParticles;
	renderCloth = false;
}


int MeshTest::GetIndex(int col, int row)
{
	return col + row * ClothMesh::numCols;
}

void MeshTest::Update(float dt)
{
	// Do verlett thingy
	//for (int i = 0; i < numParticles; i++)
	//{
	//	if (!meshParticle[i].isStatic)
	//	{
	//		meshParticle[i].currentVelocities[i] = verletIntegrator.GetAcceleration(meshParticle[i].forceAcumulator[i], meshParticle[i].particleMass);

	//		meshParticle[i].previousPositions[i] = meshParticle[i].currentPositions[i];
	//		meshParticle[i].currentPositions[i] = verletIntegrator.GetNewPosition(meshParticle[i].previousPositions[i], meshParticle[i].currentVelocities[i], dt);

	//		meshParticle[i].forceAcumulator[i] = { 0.f, 0.f, 0.f };
	//	}
	//}

	//for(int i = 0; i<steps; i++)
	//{
			//Mesh.Update(dt/steps);
	//}
	//Mesh.Render();
}

void MeshTest::RenderUpdateMesh()
{
	meshParticles->Render();
	ClothMesh::updateClothMesh(&(positions[0].x));
}

void MeshTest::SetInitialMeshPosition()
{
	for (int row = 0; row < ClothMesh::numRows; row++)
	{
		for (int col = 0; col < ClothMesh::numCols; col++)
		{
			int indx = GetIndex(col, row);
			positions[indx] = glm::vec3((row - 10)/2, 10, (col - 10)/2);
		}
	}
}

void MeshTest::SetInitialMeshParticlePosition()
{
	for (int i = 0; i < meshParticles->numMeshParticles; i++) 
	{
		meshParticles->currentPositions[i] = positions[i];
	}
}

int MeshTest::GetMaxMeshParticles()
{
	return ClothMesh::numCols * ClothMesh::numRows;
}

