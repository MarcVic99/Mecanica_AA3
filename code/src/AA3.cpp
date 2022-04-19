#include <glm\glm.hpp>
#include "EulerIntegrator.h";
#include "AA3.h"
#include "Geometry.h"
#include <imgui/imgui.h>
#include <time.h>
#include "MeshTest.h"

namespace Planes
{
	Plane bottomPlaneAA3(glm::vec3(1.f, 0.f, 1.f), glm::vec3(0.f, -1.f, 0.f));

	Plane topPlaneAA3(glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.f, -1.f, 0.f));

	Plane leftPlaneAA3(glm::vec3(-5.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
	Plane rightPlaneAA3(glm::vec3(5.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
	Plane frontPlaneAA3(glm::vec3(0.f, 0.f, 5.f), glm::vec3(0.f, 0.f, 1.f));
	Plane backPlaneAA3(glm::vec3(0.f, 0.f, -5.f), glm::vec3(0.f, 0.f, 1.f));

}

namespace Sphere
{
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	CustomSphere customSphereAA3(1.f, glm::vec3(0.f, 2.f, 0.f));
	bool resetedRadiusAA3 = true;
}

MeshTest* meshTest;

#pragma region class
AA3::AA3()
{
	srand(time(NULL));
	// Enable the rendering of particles in the framework 
	extern bool renderSphere; renderSphere = true;
	extern bool renderParticles; renderParticles = false;
	extern bool renderCloth; renderCloth = true;
}

AA3::~AA3()
{
	renderSphere = false;
	renderCloth = false;
}

void AA3::Update(float dt)
{
	//meshTest->Update(dt);
	Sphere::customSphereAA3.SphereMovement(renderSphere);
}

void AA3::RenderUpdate()
{
	meshTest->RenderUpdateMesh();
	Sphere::updateSphere(Sphere::customSphereAA3.sphereCenter, Sphere::customSphereAA3.sphereRadius);
}

void AA3::RenderGui()
{
	ImGui::Checkbox("Show sphere", &renderSphere);

	if (!renderSphere)
	{
		Sphere::customSphereAA3.sphereRadius = 0.f;
		Sphere::resetedRadiusAA3 = false;
	}
	else if (!Sphere::resetedRadiusAA3)
	{
		Sphere::customSphereAA3.sphereRadius = 1.f;
		Sphere::resetedRadiusAA3 = true;
	}


	if (renderSphere)
	{
		ImGui::InputFloat3(
			"Sphere center",
			&Sphere::customSphereAA3.sphereCenter.x // pointer to an array of 3 floats
		);

		ImGui::InputFloat(
			"Sphere Radius",
			&Sphere::customSphereAA3.sphereRadius
		);

		ImGui::RadioButton("Move left", &Sphere::customSphereAA3.sphereMovement, Sphere::customSphereAA3.LEFT);
		ImGui::RadioButton("STOP", &Sphere::customSphereAA3.sphereMovement, Sphere::customSphereAA3.STOP);
		ImGui::RadioButton("Move right", &Sphere::customSphereAA3.sphereMovement, Sphere::customSphereAA3.RIGHT);

		if (ImGui::Button("Reset sphere"))
		{
			Sphere::customSphereAA3.sphereCenter = glm::vec3(0.f, 1.f, 0.f);
		}
	}

};

#pragma endregion
