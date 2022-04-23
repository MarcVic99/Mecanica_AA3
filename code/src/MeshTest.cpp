#include "MeshTest.h"
#include "Spring.h"

MeshTest::MeshTest()
{
	renderCloth = true;
	
	positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
	SetInitialMeshPosition();

	meshParticles = new MeshParticles(ClothMesh::numCols * ClothMesh::numRows);
	SetInitialMeshParticlePositionAndVelocity();

	structuralSpringsHorizontal = std::vector<Spring>((ClothMesh::numCols - 1) * ClothMesh::numRows);
	structuralSpringsVertical = std::vector<Spring>(ClothMesh::numCols * (ClothMesh::numRows - 1));

	SetInitialPositionSprings();
}

MeshTest::~MeshTest()
{
	delete meshParticles;
	renderCloth = false;
}


int MeshTest::GetIndex(int col, int row)
{
	return col + (row * ClothMesh::numCols);
}

void MeshTest::Update()
{
	for (float row = 0; row < ClothMesh::numRows; row++)
	{
		for (float col = 0; col < ClothMesh::numCols; col++)
		{
			int indx = GetIndex(col, row);
			positions[indx] = glm::vec3(meshParticles->currentPositions[indx].x, meshParticles->currentPositions[indx].y, meshParticles->currentPositions[indx].z);
		}
	}
	ApplySpringForces();
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
	int index = 0;
	for (int row = 0; row < ClothMesh::numRows; row++) 
	{
		for (int col = 0; col < ClothMesh::numCols - 1; col++) 
		{
			// Structural Horizontal
		
			structuralSpringsHorizontal[index].particle1 = GetIndex(col, row);
			structuralSpringsHorizontal[index].particle2 = GetIndex(col + 1, row);

			structuralSpringsHorizontal[index].equilibriumDistance = GetParticleDistance(GetIndex(col, row), GetIndex(col + 1, row));

			//printf("%f \n", structuralSpringsHorizontal[index].equilibriumDistance);

			structuralSpringsHorizontal[index].constantK = 500.f;
			structuralSpringsHorizontal[index].dampingK = 100.f;
			
			index++;
		}
	}	
	
	index = 0;
	for (int row = 0; row < ClothMesh::numRows - 1; row++) 
	{
		for (int col = 0; col < ClothMesh::numCols; col++) 
		{
			// Structural Vertical
			structuralSpringsVertical[index].particle1 = GetIndex(col, row);
			structuralSpringsVertical[index].particle2 = GetIndex(col, row + 1);

			structuralSpringsVertical[index].equilibriumDistance = GetParticleDistance(GetIndex(col, row), GetIndex(col, row + 1));
			structuralSpringsVertical[index].constantK = 500.f;
			structuralSpringsVertical[index].dampingK = 100.f;

			index++;
		}
	}	
}
void MeshTest::ApplySpringForces()
{
	glm::vec3 springForce = glm::vec3(0.0f,0.0f,0.0f);

	for (int i = 0; i < structuralSpringsHorizontal.size(); i++)
	{
		springForce = structuralSpringsHorizontal[i].GetStrenghtBetweenTwoPositions(meshParticles->currentPositions[structuralSpringsHorizontal[i].particle1],
			meshParticles->currentPositions[structuralSpringsHorizontal[i].particle2],
			meshParticles->currentVelocities[structuralSpringsHorizontal[i].particle1],
			meshParticles->currentVelocities[structuralSpringsHorizontal[i].particle2]);

		SetAcceleration(structuralSpringsHorizontal[i].particle1, springForce);
		SetAcceleration(structuralSpringsHorizontal[i].particle2, -springForce);
	}


	for (int i = 0; i < structuralSpringsVertical.size(); i++)
	{
		springForce = structuralSpringsVertical[i].GetStrenghtBetweenTwoPositions(meshParticles->currentPositions[structuralSpringsVertical[i].particle1],
			meshParticles->currentPositions[structuralSpringsVertical[i].particle2],
			meshParticles->currentVelocities[structuralSpringsVertical[i].particle1],
			meshParticles->currentVelocities[structuralSpringsVertical[i].particle2]);

		SetAcceleration(structuralSpringsVertical[i].particle1, springForce);
		SetAcceleration(structuralSpringsVertical[i].particle2, -springForce);
	}


}


void MeshTest::SetAcceleration(int index, glm::vec3 springForce)
{
	meshParticles->forceAcumulator[index] += springForce / meshParticles->particleMass;
}

float MeshTest::GetParticleDistance(int firstParticleIndx, int secondParticleIndx)
{
	return glm::distance(meshParticles->startingPositions[firstParticleIndx], meshParticles->startingPositions[secondParticleIndx]);
}

glm::vec3 MeshTest::GetParticlePosition(int particleId)
{
	return meshParticles->currentPositions[particleId];
}

