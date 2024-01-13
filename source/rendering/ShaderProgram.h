#pragma once
#include <GL/glew.h>
#include "Shader.h"

class ShaderProgram
{
private:
	unsigned int programID;

public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		 programID = glCreateProgram();

		 Shader vertexShader(GL_VERTEX_SHADER ,vertexShaderPath);
		 glAttachShader(programID, vertexShader.GetShaderID());

		 Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
		 glAttachShader(programID, fragmentShader.GetShaderID());

		 glLinkProgram(programID);
		 glValidateProgram(programID);

		 GetProgramIV(GL_VALIDATE_STATUS);

		 glUseProgram(programID);
	}

	ShaderProgram()
	{
		programID = glCreateProgram();
	}

	void AttatchShaders(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		Shader vertexShader(GL_VERTEX_SHADER, vertexShaderPath);
		glAttachShader(programID, vertexShader.GetShaderID());

		Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
		glAttachShader(programID, fragmentShader.GetShaderID());

		glLinkProgram(programID);
		glValidateProgram(programID);

		GetProgramIV(GL_VALIDATE_STATUS);

		glUseProgram(programID);
	}

	void useProgram()
	{
		glUseProgram(programID);
	}

	~ShaderProgram()
	{
		glDeleteProgram(programID);
	}

private:
	void GetProgramIV(int queryParameter)
	{
		int succeeded;
		glGetProgramiv(programID, queryParameter, &succeeded);

		if (succeeded == false)
		{
			GLsizei length;
			char error[1024];
			glGetProgramInfoLog(programID, 1024, &length, error);

			std::cout << "The Shader program has encountered error " << error << std::endl;
		}
	}
};