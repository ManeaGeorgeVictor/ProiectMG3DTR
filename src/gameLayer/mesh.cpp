#include "mesh.h"



// position: x y z
// 

//loads the model data
void Mesh::loadFromData(float *data, 
	int size)
{

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), 0);

	glBindVertexArray(0);

	vertexCount = size / (sizeof(float) * 3);
		
}
