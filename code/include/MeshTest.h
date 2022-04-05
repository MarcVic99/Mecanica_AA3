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
	MeshTest() { renderCloth = true; }

	int GetIndex(int col, int row)
	{
		return col + row * ClothMesh::numCols;
	}
	
	void RenderUpdate()
	{
		glm::vec3* positions = new glm::vec3[ClothMesh::numCols * ClothMesh::numRows];
		for (int row = 0; row < ClothMesh::numRows; row++)
		{
			for (int col = 0; col < ClothMesh::numCols; col++)
			{
				int indx = GetIndex(col, row);

				positions[indx] = glm::vec3(row, col, 0.f);
			}
		}
		ClothMesh::updateClothMesh(&(positions[0].x));
	}

	~MeshTest() { renderCloth = false; }

	void Update(float dt) {}
};

