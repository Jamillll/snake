#pragma once
#include "../rendering/Vertex.h"

struct Cell
{
	Vertex vertices[4];

	void ChangeColour(float r, float g, float b)
	{
		for (size_t i = 0; i < 4; i++)
		{
			vertices[i].r = r;
			vertices[i].g = g;
			vertices[i].b = b;
		}
	}
};

class Grid
{
public:
	int axisLength = 20;
	Cell cells[400];

	unsigned int indices[2400];

	Grid()
	{
		int cellWidth = 1900 / axisLength;

		int cellPlacementY = cellWidth / 2;
		for (size_t y = 0; y < axisLength; y++)
		{
			int cellPlacementX = cellWidth / 2;
			for (size_t x = 0; x < axisLength; x++)
			{
				int index = (y * axisLength) + x;

				cells[index].vertices[0].x = cellPlacementX - cellWidth / 2;
				cells[index].vertices[0].y = cellPlacementY - cellWidth / 2;

				cells[index].vertices[1].x = cellPlacementX + cellWidth / 2;
				cells[index].vertices[1].y = cellPlacementY - cellWidth / 2;

				cells[index].vertices[2].x = cellPlacementX - cellWidth / 2;
				cells[index].vertices[2].y = cellPlacementY + cellWidth / 2;

				cells[index].vertices[3].x = cellPlacementX + cellWidth / 2;
				cells[index].vertices[3].y = cellPlacementY + cellWidth / 2;

				cells[index].ChangeColour(1.0, 1.0, 1.0);

				indices[index * 6 + 0] = index * 4 + 0;
				indices[index * 6 + 1] = index * 4 + 1;
				indices[index * 6 + 2] = index * 4 + 3;

				indices[index * 6 + 3] = index * 4 + 0;
				indices[index * 6 + 4] = index * 4 + 2;
				indices[index * 6 + 5] = index * 4 + 3;

				cellPlacementX += cellWidth + 5;
			}

			cellPlacementY += cellWidth + 5;
		}
	}

	void Update()
	{
		for (size_t i = 0; i < 400; i++)
		{
			SetCellColour(i, 0.1, 0.5, 0.1);
		}
	}

	void SetCellColour(int x, int y, float r, float g, float b)
	{
		if (x >= 20 || y >= 20 || x < 0 || y < 0)
		{
			return;
		}

		cells[(y * axisLength) + x].ChangeColour(r, g, b);
	}

	void SetCellColour(int index, float r, float g, float b)
	{
		cells[index].ChangeColour(r, g, b);
	}
};