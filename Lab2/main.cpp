#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>
#include <iostream>
#include "Shader.h"
#include "VAO.h"

// Macro for indexing vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Shader shaders[2];
VAO VAOs[2];

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Transform objects
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(15.0f), glm::vec3(1.0, 1.0, 0.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	shaders[0].Use();
	shaders[0].SetMat4("transform", trans);
	glBindVertexArray(VAOs[0].GetID());
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	shaders[1].Use();
	shaders[1].SetMat4("transform", trans);
	glBindVertexArray(VAOs[1].GetID());
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	glutSwapBuffers();
}

// Split executable path into vector of seperate directories
std::vector<std::string> tokenizer(std::string s, char del)
{
	std::vector<std::string> output;
	std::stringstream ss(s);
	std::string word;
	while (!ss.eof()) {
		getline(ss, word, del);
		output.push_back(word);
	}
	return output;
}

void init(){
	// Create the vertices of triangular based pyramid and cube
	std::vector<glm::vec3> vertices_p = { 
		glm::vec3(-0.5f, 0.0f, 1.0f),
		glm::vec3(-1.0f, -0.5f, 0.0f),
		glm::vec3(0.0f, -0.5f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f) 
	};
	std::vector<glm::vec3> vertices_c = { 
		glm::vec3(0.0f, -0.5f, 0.0f),
		glm::vec3(0.0f, -0.5f, 1.0f),
		glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec3(0.0f, 0.5f, 1.0f),
		glm::vec3(1.0f, -0.5f, 0.0f),
		glm::vec3(1.0f, -0.5f, 1.0f),
		glm::vec3(1.0f, 0.5f, 0.0f),
		glm::vec3(1.0f, 0.5f, 1.0f)
	};

	// Create a color array that identfies the colors of each vertex (format R, G, B, A)
	glm::vec4 red = { 1.0f, 0.0f, 0.0f, 1.0f};
	glm::vec4 green = { 0.0f, 1.0f, 0.0f, 1.0f };
	glm::vec4 blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
	std::vector<glm::vec4> color_p = { red, red, green, blue };
	std::vector<glm::vec4> color_c = { red, green, blue, red, green, blue, red, green};

	// Create the index buffer of the triangular based pyramid and cube
	std::vector<GLuint> indices_p = {
		0, 1, 2,
		0, 1, 3,
		0, 2, 3,
		1, 2, 3
	};
	std::vector<GLuint> indices_c = {
		1, 3, 5,	3, 5, 7,
		0, 1, 4,	1, 4, 5,
		4, 5, 6,	5, 6, 7,
		2, 3, 6,	3, 6, 7,
		0, 1, 2,	1, 2, 3,
		1, 3, 5,	3, 5, 7
	};

	std::string pVS = "VertexShader.txt";
	std::string pFS[] = { "FragmentShader0.txt", "FragmentShader1.txt" };

	// Shaders paths are incorrect so program crashes 
	shaders[0] = Shader(pVS.c_str(), pFS[0].c_str());
	VAOs[0] = VAO(vertices_p, color_p, indices_p, shaders[0].GetID());
	
	shaders[1] = Shader(pVS.c_str(), pFS[1].c_str());
	VAOs[1] = VAO(vertices_c, color_c, indices_c, shaders[1].GetID());
}

int main(int argc, char** argv){
	// Set up the window
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab 2");
	// Tell glut where the display function is
	glutDisplayFunc(display);

	 // A call to glewInit() must be done after glut is initialized!
    GLenum res = glewInit();
	// Check for any errors
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

	// Set up your objects and shaders
	init();

	// Begin infinite event loop
	glutMainLoop();
    return 0;
}