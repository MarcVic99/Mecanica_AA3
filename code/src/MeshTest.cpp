#include "MeshTest.h"

MeshTest::MeshTest()//(int width, int height)
{
	renderCloth = true;
	
	currentPositions = new glm::vec3[GetMaxMeshParticles()];
	currentVelocities = new glm::vec3[GetMaxMeshParticles()];

	startingPositions = new glm::vec3[GetMaxMeshParticles()];
	startingVelocities = new glm::vec3[GetMaxMeshParticles()];

	previousPositions = new glm::vec3[GetMaxMeshParticles()];
	previousVelocities = new glm::vec3[GetMaxMeshParticles()];

	startingPositions = new glm::vec3[GetMaxMeshParticles()];
	startingVelocities = new glm::vec3[GetMaxMeshParticles()];
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
