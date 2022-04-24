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

	bendingSpringsHorizontal = std::vector<Spring>((ClothMesh::numCols - 2) * ClothMesh::numRows);
	bendingSpringsVertical = std::vector<Spring>(ClothMesh::numCols * (ClothMesh::numRows - 2));

	shearSpringsRight = std::vector<Spring>((ClothMesh::numCols - 1) * (ClothMesh::numRows - 1));
	shearSpringsLeft = std::vector<Spring>((ClothMesh::numCols - 1) * (ClothMesh::numRows - 1));

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

			structuralSpringsHorizontal[index].constantK = 500.f;
			structuralSpringsHorizontal[index].dampingK = 20.f;
			
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
			structuralSpringsVertical[index].dampingK = 20.f;

			index++;
		}
	}	
	
	index = 0;
	for (int row = 0; row < ClothMesh::numRows; row++)
	{
		for (int col = 0; col < ClothMesh::numCols - 2; col++)
		{
			// Bending Horizontal
			bendingSpringsHorizontal[index].particle1 = GetIndex(col, row);
			bendingSpringsHorizontal[index].particle2 = GetIndex(col + 2, row);

			bendingSpringsHorizontal[index].equilibriumDistance = GetParticleDistance(GetIndex(col, row), GetIndex(col + 2, row));
			bendingSpringsHorizontal[index].constantK = 1000.f;
			bendingSpringsHorizontal[index].dampingK = 40.f;

			index++;
		}
	}

	index = 0;
	for (int row = 0; row < ClothMesh::numRows - 2; row++)
	{
		for (int col = 0; col < ClothMesh::numCols; col++)
		{
			// Bending Vertical
			bendingSpringsVertical[index].particle1 = GetIndex(col, row);
			bendingSpringsVertical[index].particle2 = GetIndex(col, row + 2);

			bendingSpringsVertical[index].equilibriumDistance = GetParticleDistance(GetIndex(col, row), GetIndex(col, row + 2));
			bendingSpringsVertical[index].constantK = 1000.f;
			bendingSpringsVertical[index].dampingK = 40.f;

			index++;
		}
	}

	index = 0;
	for (int row = 0; row < ClothMesh::numRows - 1; row++)
	{
		for (int col = 0; col < ClothMesh::numCols - 1; col++)
		{
			// Shear Right
			shearSpringsRight[index].particle1 = GetIndex(col, row);
			shearSpringsRight[index].particle2 = GetIndex(col + 1, row + 1);

			shearSpringsRight[index].equilibriumDistance = GetParticleDistance(GetIndex(col, row), GetIndex(col + 1, row + 1));
			shearSpringsRight[index].constantK = 700.f;
			shearSpringsRight[index].dampingK = 25.f;

			index++;
		}
	}

	index = 0;
	for (int row = 0; row < ClothMesh::numRows - 1; row++)
	{
		for (int col = 1; col < ClothMesh::numCols; col++)
		{
			// Shear Left
			shearSpringsLeft[index].particle1 = GetIndex(col, row);
			shearSpringsLeft[index].particle2 = GetIndex(col - 1, row + 1);

			shearSpringsLeft[index].equilibriumDistance = GetParticleDistance(GetIndex(col, row), GetIndex(col - 1, row + 1));
			shearSpringsLeft[index].constantK = 700.f;
			shearSpringsLeft[index].dampingK = 25.f;

			index++;
		}
	}
}
void MeshTest::ApplySpringForces()
{
	glm::vec3 springForce = glm::vec3(0.0f, 0.0f, 0.0f);

	// == STRUCTURAL ==
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

	// == BENDING ==
	for (int i = 0; i < bendingSpringsHorizontal.size(); i++)
	{
		springForce = bendingSpringsHorizontal[i].GetStrenghtBetweenTwoPositions(meshParticles->currentPositions[bendingSpringsHorizontal[i].particle1],
			meshParticles->currentPositions[bendingSpringsHorizontal[i].particle2],
			meshParticles->currentVelocities[bendingSpringsHorizontal[i].particle1],
			meshParticles->currentVelocities[bendingSpringsHorizontal[i].particle2]);

		SetAcceleration(bendingSpringsHorizontal[i].particle1, springForce);
		SetAcceleration(bendingSpringsHorizontal[i].particle2, -springForce);
	}

	for (int i = 0; i < bendingSpringsVertical.size(); i++)
	{
		springForce = bendingSpringsVertical[i].GetStrenghtBetweenTwoPositions(meshParticles->currentPositions[bendingSpringsVertical[i].particle1],
			meshParticles->currentPositions[bendingSpringsVertical[i].particle2],
			meshParticles->currentVelocities[bendingSpringsVertical[i].particle1],
			meshParticles->currentVelocities[bendingSpringsVertical[i].particle2]);

		SetAcceleration(bendingSpringsVertical[i].particle1, springForce);
		SetAcceleration(bendingSpringsVertical[i].particle2, -springForce);
	}

	// == SHEAR ==
	for (int i = 0; i < shearSpringsRight.size(); i++)
	{
		springForce = shearSpringsRight[i].GetStrenghtBetweenTwoPositions(meshParticles->currentPositions[shearSpringsRight[i].particle1],
			meshParticles->currentPositions[shearSpringsRight[i].particle2],
			meshParticles->currentVelocities[shearSpringsRight[i].particle1],
			meshParticles->currentVelocities[shearSpringsRight[i].particle2]);

		SetAcceleration(shearSpringsRight[i].particle1, springForce);
		SetAcceleration(shearSpringsRight[i].particle2, -springForce);
	}

	for (int i = 0; i < shearSpringsLeft.size(); i++)
	{
		springForce = shearSpringsLeft[i].GetStrenghtBetweenTwoPositions(meshParticles->currentPositions[shearSpringsLeft[i].particle1],
			meshParticles->currentPositions[shearSpringsLeft[i].particle2],
			meshParticles->currentVelocities[shearSpringsLeft[i].particle1],
			meshParticles->currentVelocities[shearSpringsLeft[i].particle2]);

		SetAcceleration(shearSpringsLeft[i].particle1, springForce);
		SetAcceleration(shearSpringsLeft[i].particle2, -springForce);
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