#pragma once
#include <glm/glm.hpp>
#include "Simulator.h"

extern bool renderCloth;

namespace ClothMesh
{
	extern void updateClothMesh(float* aray_data);
	extern const int numCols;
	extern const int numRows;
}

class MeshTest : public Simulator
{
public:
	MeshTest(int width, int height);

	int GetIndex(int col, int row);
	
	void RenderUpdate();

	~MeshTest();

	void Update(float dt) {}

private:

	int meshWidth;
	int meshHeight;
};

