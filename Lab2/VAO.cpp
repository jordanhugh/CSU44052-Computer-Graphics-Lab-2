#include "VAO.h"

VAO::VAO() {}

VAO::VAO(std::vector<glm::vec3> vert, std::vector<glm::vec4> clr, std::vector<GLuint> inds, GLuint shaderProgramID)
{
	vertices = vert;
	color = clr;
	indices = inds;
	numVertices = vertices.size();
	numIndices = indices.size();

	GenerateVertexBufferObject();
	LinkCurrentBuffertoShader(shaderProgramID);
	GenerateIndexBufferObject();
}

void VAO::GenerateVertexBufferObject() 
{
	// Genderate a generic buffer object, called VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	// In OpenGL, we bind (make active) the handle to a target name and then execute commands on that target
	// Buffer will contain an array of vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// After binding, we now fill our object with data, everything in "Vertices" goes to the GPU
	glBufferData(GL_ARRAY_BUFFER, numVertices * 7 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	// if you have more data besides vertices (e.g., vertex colours or normals), use glBufferSubData to tell the buffer when the vertices array ends and when the colors start
	glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * 3 * sizeof(GLfloat), &vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(GLfloat), numVertices * 4 * sizeof(GLfloat), &color[0]);
}

void VAO::LinkCurrentBuffertoShader(GLuint shaderProgramID) 
{
	// Find the location of the variables that we will be using in the shader program
	GLuint positionID = glGetAttribLocation(shaderProgramID, "vPosition");
	GLuint colorID = glGetAttribLocation(shaderProgramID, "vColor");
	
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);

	// Have to enable this
	glEnableVertexAttribArray(positionID);
	// Tell it where to find the position data in the currently active buffer (at index positionID)
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Similarly, for the color data.
	glEnableVertexAttribArray(colorID);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(numVertices * 3 * sizeof(GLfloat)));
}

void VAO::GenerateIndexBufferObject()
{
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindVertexArray(ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	std::cout << numIndices << std::endl;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

GLuint VAO::GetID() 
{
	return ID;
}