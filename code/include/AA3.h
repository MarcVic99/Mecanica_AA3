#pragma once
#pragma once
#include "Simulator.h"
#include "ParticleSystem.h"

namespace Sphere {
	extern void updateSphere(glm::vec3 pos, float radius);
}

extern bool renderSphere;
extern bool renderCloth;

class AA3 : public Simulator
{
public:
	AA3();
	~AA3();

	void Update(float dt);
	void RenderUpdate();
	void RenderGui();

private:
};



