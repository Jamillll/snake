#pragma once

#include <GL\glew.h>
#include "Vertex.h"

class VertexArray
{
private:
	unsigned int vertexArrayID;
	unsigned int vertexBufferID;
	unsigned int elementBufferID;

	const void* vertexData = nullptr;
	unsigned int vertexDataSize = NULL;
	const void* indexData = nullptr;
	unsigned int indexDataSize = NULL;

	int usage = GL_DYNAMIC_DRAW;

public:
	VertexArray(const void* vertexArray, unsigned int vertexArraySize, const void* indexArray, unsigned int indexArraySize)
	{
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		glGenBuffers(1, &vertexBufferID);
		setVertexData(vertexArray, vertexArraySize);

		glVertexAttribPointer(0, 2, GL_INT, false, sizeof(Vertex), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)(sizeof(int) * 2));
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &elementBufferID);
		setIndexData(indexArray, indexArraySize);
	}

	VertexArray()
	{
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

		glVertexAttribPointer(0, 2, GL_INT, false, sizeof(Vertex), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)(sizeof(int) * 2));
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &elementBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
	}

	void setVertexData(const void* vertexArray, unsigned int vertexArraySize)
	{
		vertexData = vertexArray;
		vertexDataSize = vertexArraySize;

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, usage);
	}

	void setIndexData(const void* indexArray, unsigned int indexArraySize)
	{
		indexData = indexArray;
		indexDataSize = indexArraySize;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, usage);
	}

	void UpdateBuffers()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, usage);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, usage);
	}

	void setUsage(int newUsage)
	{
		usage = newUsage;
	}

	unsigned int getIndexCount()
	{
		return indexDataSize / sizeof(unsigned int);
	}

	~VertexArray()
	{
		glDeleteVertexArrays(1, &vertexArrayID);
		glDeleteBuffers(1, &vertexBufferID);
		glDeleteBuffers(1, &elementBufferID);
	}
};