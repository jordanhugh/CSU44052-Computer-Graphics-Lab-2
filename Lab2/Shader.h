#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
	GLuint ID = 0;

	static char* ReadShaderSource(const char* shaderFile);
	static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(static const char* pVS, static const char* pFS);

public:
	Shader();
	Shader(static const char* pVS, static const char* pFS);
	void Use();
	GLuint GetID();
	void SetMat4(const std::string& name, const glm::mat4& mat);
};