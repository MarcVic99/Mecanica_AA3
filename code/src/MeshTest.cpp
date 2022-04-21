#include "MeshTest.h"

MeshTest::MeshTest()
{
	renderCloth = true;
	
	positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
	SetInitialMeshPosition();

	meshParticles = new MeshParticles(ClothMesh::numCols * ClothMesh::numRows);
	SetInitialMeshParticlePositionAndVelocity();
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

void MeshTest::SetInitialMeshParticlePositionAndVelocity()
{
	for (int i = 0; i < meshParticles->numMeshParticles; i++) 
	{
		meshParticles->currentPositions[i] = positions[i];
		meshParticles->currentVelocities[i] = glm::vec3(0,0,0);
	}
}

int MeshTest::GetNumMeshParticles()
{
	return meshParticles->numMeshParticles;
}

int MeshTest::GetNumCols()
{
	return ClothMesh::numCols;
}

int MeshTest::GetNumRows()
{
	return ClothMesh::numRows;
}