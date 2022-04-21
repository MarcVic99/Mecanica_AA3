#include "VerlettIntegrator.h"

VerlettIntegrator::VerlettIntegrator()
{
}

VerlettIntegrator::~VerlettIntegrator()
{
}


void VerlettIntegrator::StepVerlett(MeshTest* mesh, float dt)
{
	int currParticle = 0;

	Spring spring; // Test spring value (MUST BE DELETED & CHANGED FOR ARRAY)
	
	glm::vec3 previousPosition;
	glm::vec3 currentPosition;
	glm::vec3 nextPosition;

	glm::vec3 currentVelocity;

	for (int i = 0; i < mesh->GetNumRows(); i++)
	{
		for (int j = 0; j < mesh->GetNumCols(); j++)
		{
			previousPosition = mesh->meshParticles->GetPreviousParticlePosition(currParticle);
			currentPosition = mesh->meshParticles->GetCurrentParticlePosition(currParticle);
			
			if (!mesh->meshParticles->isStatic[currParticle])
			{
				// Calculate forces
				//mesh->meshParticles->forceAcumulator[currParticle] = glm::vec3(0.f, -9.8f, 0.f);
				//if (j == 0)
				//{
				//	// Particle on the left
				//	mesh->meshParticles->forceAcumulator[currParticle] +=
				//		spring.GetStrenghtBetweenTwoPositions(currentPosition, mesh->meshParticles->GetCurrentParticlePosition(currParticle + 1),
				//			currentVelocity, mesh->meshParticles->GetCurrentParticleVelocity(i + 1));
				//}
				//else if (j == mesh->GetNumCols())
				//{
				//	// Paricle on the right
				//	mesh->meshParticles->forceAcumulator[currParticle] -=
				//		spring.GetStrenghtBetweenTwoPositions(mesh->meshParticles->GetCurrentParticlePosition(currParticle - 1), currentPosition,
				//			mesh->meshParticles->GetCurrentParticleVelocity(i - 1), currentVelocity);
				//}
				//else
				//{
				//	mesh->meshParticles->forceAcumulator[currParticle] +=
				//		(spring.GetStrenghtBetweenTwoPositions(currentPosition, mesh->meshParticles->GetCurrentParticlePosition(currParticle + 1),
				//			currentVelocity, mesh->meshParticles->GetCurrentParticleVelocity(i + 1))
				//			- spring.GetStrenghtBetweenTwoPositions(mesh->meshParticles->GetCurrentParticlePosition(currParticle - 1), currentPosition,
				//				mesh->meshParticles->GetCurrentParticleVelocity(i - 1), currentVelocity));
				//}

				//Xt+1 = Xt + (Xt - Xt-1) + f/m * dt^2
				nextPosition = currentPosition + (currentPosition - previousPosition) +
					GetAcceleration(mesh->meshParticles->forceAcumulator[currParticle], mesh->meshParticles->particleMass) * (dt * dt);
				
				// Set values
				mesh->meshParticles->SetParticlePosition(currParticle, nextPosition);

				// Reset values
				mesh->meshParticles->ResetParticleForce(currParticle);
			}
			else {
				/*printf("Particle: %i Static: %d \n", currParticle, mesh->meshParticles->isStatic[currParticle]);
				printf("Particle: %i X: %f\n", currParticle, mesh->meshParticles->currentPositions[currParticle].x);
				printf("Particle: %i Y: %f\n", currParticle, mesh->meshParticles->currentPositions[currParticle].y);
				printf("Particle: %i Z: %f\n", currParticle, mesh->meshParticles->currentPositions[currParticle].z);*/
				mesh->meshParticles->SetParticlePosition(currParticle, currentPosition);
			}
			currParticle++;
		}
	}
	currParticle = 0;
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