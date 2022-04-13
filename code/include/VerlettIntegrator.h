#pragma once

#include <glm\glm.hpp>
#include "MeshTest.h"

class VerlettIntegrator
{
public:
	VerlettIntegrator();
	~VerlettIntegrator();

	static void StepVerlett(MeshTest mesh, float dt);

private:
	VerlettIntegrator* verlettIntegrator;
};

