#include "VerlettIntegrator.h"

VerlettIntegrator::VerlettIntegrator()
{
}

VerlettIntegrator::~VerlettIntegrator()
{
}


void VerlettIntegrator::StepVerlett(MeshTest* mesh, float dt)
{
	Spring spring(5.f, 5.f, glm::vec3(1.f, 1.f, 1.f)); // Test spring value (MUST BE DELETED & CHANGED FOR ARRAY)
	glm::vec3 previousPosition;
	glm::vec3 currentPosition;
	glm::vec3 nextPosition;

	glm::vec3 currentVelocity;

	for (int i = 0; i < mesh->GetNumMeshParticles(); i++)
	{
		previousPosition = mesh->meshParticles->GetPreviousParticlePosition(i);
		currentPosition = mesh->meshParticles->GetCurrentParticlePosition(i);
		
		// Calculate forces
		mesh->meshParticles->forceAcumulator[i] = glm::vec3(0.f, -9.8f, 0.f);
		if (i == 0 || i == mesh->GetNumCols() + 1 || i == mesh->GetNumCols() * 2 + 1) // This is not done 'cause there must be a better way
		{
			mesh->meshParticles->forceAcumulator[i] += spring.GetStrenghtBetweenTwoPositions(currentPosition, mesh->meshParticles->GetCurrentParticlePosition(i + 1));
		}
		else if (i == mesh->GetNumCols() || i == mesh->GetNumCols() * 2 || i == mesh->GetNumCols() * 3) // This is not done 'cause there must be a better way
		{
			mesh->meshParticles->forceAcumulator[i] -= spring.GetStrenghtBetweenTwoPositions(mesh->meshParticles->GetCurrentParticlePosition(i - 1), currentPosition);
		}
		else
		{
			mesh->meshParticles->forceAcumulator[i] += (spring.GetStrenghtBetweenTwoPositions(currentPosition, mesh->meshParticles->GetCurrentParticlePosition(i + 1))
													- spring.GetStrenghtBetweenTwoPositions(mesh->meshParticles->GetCurrentParticlePosition(i - 1), currentPosition));
		}

		//Xt+1 = Xt + (Xt - Xt-1) + f/m * dt^2
		nextPosition = currentPosition + (currentPosition - previousPosition) + 
						GetAcceleration(mesh->meshParticles->forceAcumulator[i], mesh->meshParticles->particleMass) * (dt * dt);
		mesh->meshParticles->previousPositions[i] = currentPosition;
		mesh->meshParticles->currentPositions[i] = nextPosition;

		// Reset values
		mesh->meshParticles->forceAcumulator[i] = glm::vec3(0.f, -9.8f, 0.f);
	}
}

glm::vec3 VerlettIntegrator::GetAcceleration(glm::vec3 forceAcum, float mass)
{
	return forceAcum / mass;
}

glm::vec3 VerlettIntegrator::GetNewPosition(glm::vec3 currPos, glm::vec3 lastPos, glm::vec3 accel, float dt)
{
	return currPos + (currPos - lastPos) + accel * (dt * dt);
}

glm::vec3 VerlettIntegrator::GetNewVelocity(glm::vec3 newPos, glm::vec3 currPos, float dt)
{
	return (newPos - currPos) / dt;
}