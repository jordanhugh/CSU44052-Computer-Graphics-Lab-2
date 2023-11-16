#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class VAO 
{
private:
	GLuint ID = 0;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> color;
	GLuint numVertices = 0;
	std::vector<GLuint> indices;
	GLuint numIndices = 0;

	void GenerateVertexBufferObject();
	void LinkCurrentBuffertoShader(GLuint shaderProgramID);
	void GenerateIndexBufferObject();

public:
	VAO();
	VAO(std::vector<glm::vec3> vert, std::vector<glm::vec4> clr, std::vector<GLuint> inds, GLuint shaderProgramID);
	GLuint GetID();
};