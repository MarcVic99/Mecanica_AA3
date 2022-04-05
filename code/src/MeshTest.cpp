#include "MeshTest.h"

MeshTest::MeshTest(int width, int height)
{
	renderCloth = true;
	meshWidth = width;
	meshHeight = height;
}

int MeshTest::GetIndex(int col, int row)
{
	return col + row * ClothMesh::numCols;
}

void MeshTest::RenderUpdate()
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

MeshTest::~MeshTest()
{ 
	renderCloth = false; 
}
