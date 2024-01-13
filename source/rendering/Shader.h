#pragma once
#include <GL/glew.h>
#include <fstream>
#include <string>
#include <iostream>

class Shader
{
private:
	unsigned int shaderID;

public:
	Shader(int shaderType, const char* shaderPath)
	{
		shaderID = glCreateShader(shaderType);

		std::string shaderSourceString = ParseShader(shaderPath);
		const char* shaderSource = shaderSourceString.c_str();

		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);

		int succeeded;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succeeded);

		if (succeeded == false)
		{
			GLsizei length;
			char error[1024];
			glGetShaderInfoLog(shaderID, 1024, &length, error);

			std::cout << "Shader type: " << shaderType << " has encountered error " << error << std::endl;
		}
	}

	unsigned int GetShaderID()
	{
		return shaderID;
	}

	~Shader()
	{
		glDeleteShader(shaderID);
	}

private:
	std::string ParseShader(const char* shaderPath)
	{
		using namespace std;

		fstream file(shaderPath);
		string currentLine;
		string shader;

		while (getline(file, currentLine))
		{
			shader += currentLine + "\n";
		}

		return shader;
	}

	void GetShaderErrors(unsigned int shaderID, unsigned int logQueryEnum, const char* shaderType)
	{
		int succeeded;
		glGetShaderiv(shaderID, logQueryEnum, &succeeded);

		if (succeeded == false)
		{
			GLsizei length;
			char error[1024];
			glGetShaderInfoLog(shaderID, 1024, &length, error);

			std::cout << shaderType << " has encountered error " << error << std::endl;
		}
	}
};