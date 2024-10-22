#pragma once

#include <glad/glad.h>


class Mesh
{
public:

	GLuint vao;
	GLuint vbo; 
	int vertexCount;

	void loadFromData(float *data, int size);
};
