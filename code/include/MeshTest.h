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

class MeshTest
{
public:
	MeshTest();// (int width, int height);

	int GetIndex(int col, int row);
	
	void RenderUpdateMesh();

	~MeshTest();

	void Update(float dt);

private:

	int meshWidth = 14;
	int meshHeight = 18;
};

