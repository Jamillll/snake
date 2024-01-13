#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "VertexArray.h"
#include "ShaderProgram.h"

class Renderer
{
private:
	GLFWwindow* targetWindow;

	VertexArray vertexArray;
	ShaderProgram basicShaders;

public:
	Renderer(GLFWwindow* window)
	{
		targetWindow = window;
		glClearColor(0, 0.3, 0, 1);

		const char* vertexShaderPath = "source\\rendering\\shaders\\VertexShader.shader";
		const char* fragmentShaderPath = "source\\rendering\\shaders\\FragmentShader.shader";

		basicShaders.AttatchShaders(vertexShaderPath, fragmentShaderPath);
	}

	void SetVertexDataPointer(const void* vertexData, unsigned int vertexDataSize)
	{
		vertexArray.setVertexData(vertexData, vertexDataSize);
	}

	void SetIndexDataPointer(const void* indexArray, unsigned int indexArraySize)
	{
		vertexArray.setIndexData(indexArray, indexArraySize);
	}
	
	void Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		vertexArray.UpdateBuffers();
		glDrawElements(GL_TRIANGLES, vertexArray.getIndexCount(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(targetWindow);
	}
};
