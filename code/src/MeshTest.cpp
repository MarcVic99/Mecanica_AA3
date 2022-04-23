#include "MeshTest.h"
#include "Spring.h"

MeshTest::MeshTest()
{
	renderCloth = true;
	
	positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
	SetInitialMeshPosition();

	meshParticles = new MeshParticles(ClothMesh::numCols * ClothMesh::numRows);
	SetInitialMeshParticlePositionAndVelocity();

	//structuralSprings = new Spring[(ClothMesh::numCols - 1) * (ClothMesh::numRows - 1)];
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
	for (float row = 0; row < ClothMesh::numRows; row++)
	{
		for (float col = 0; col < ClothMesh::numCols; col++)
		{
			int indx = GetIndex(col, row);
			positions[indx] = glm::vec3((row - 10), 10, (col - 5));
			positions[indx] = positions[indx] / glm::vec3(3, 1, 3);
		}
	}
}

void MeshTest::SetInitialMeshParticlePositionAndVelocity()
{
	for (int i = 0; i < meshParticles->numMeshParticles; i++) 
	{
		meshParticles->currentPositions[i] = positions[i];
		meshParticles->currentVelocities[i] = glm::vec3(0,0,0);
		meshParticles->previousPositions[i] = positions[i];
		meshParticles->startingPositions[i] = positions[i];
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

void MeshTest::SetInitialPositionSprings()
{	
	int structuralK = 500.0f;
	//float structuralEquilibriumD :
	int structuralDampingK = 20.0f;

	int index = 0;
	for (int row = 0; row < ClothMesh::numRows; row++) 
	{
		for (int col = 0; col < ClothMesh::numCols - 1; col++) {
			//structuralSprings = Spring[index]();
			index++;
		}
	}
}
void MeshTest::ApplySpringForces()
{

}

float MeshTest::GetParticleDistance()
{
	return glm::distance(meshParticles->startingPositions[0], meshParticles->startingPositions[1]);
}
