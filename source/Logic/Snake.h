#pragma once
#include <vector>
#include <GLFW/glfw3.h>

struct SnakePart
{
	int x, y;
	int directionX, directionY;
};

class Snake
{
public:
	std::vector<SnakePart> snakeList;

	int movementTimer = 0;
	int movementWait = 7;

	int graceDuration = 3;
	int currentTurn = 0;

	bool alive;
	bool hasStarted;

	bool toAddPart;

	Snake()
	{
		SetupSnake();
	}

	void SetupSnake()
	{
		snakeList.clear();

		snakeList.push_back({ 9, 10, 0, 0 });
		snakeList.push_back({ 9, 10, 0, 0 });
		snakeList.push_back({ 9, 10, 0, 0 });
		snakeList.push_back({ 9, 10, 0, 0 });

		alive = true;
		hasStarted = false;
		toAddPart = false;
		movementTimer = 0;
		currentTurn = 0;
	}

	void Update(GLFWwindow* window)
	{
		getPlayerInput(window);

		if (alive == false)
		{
			return;
		}

		if (hasStarted == false)
		{
			return;
		}

		if (movementTimer == 0)
		{
			for (size_t i = 0; i < snakeList.size(); i++)
			{
				snakeList[i].x += snakeList[i].directionX;
				snakeList[i].y += snakeList[i].directionY;
			}

			for (size_t i = snakeList.size() - 1; i > 0; i--)
			{
				if (i - 1 < 0)
				{
					break;
				}

				snakeList[i].directionX = snakeList[i - 1].directionX;
				snakeList[i].directionY = snakeList[i - 1].directionY;
			}

			if (toAddPart == true)
			{
				snakeList.push_back({ snakeList[snakeList.size() - 1] });
				snakeList[snakeList.size() - 1].x -= snakeList[snakeList.size() - 1].directionX;
				snakeList[snakeList.size() - 1].y -= snakeList[snakeList.size() - 1].directionY;

				toAddPart = false;
			}

			DeathCheck();
		}

		movementTimer++;

		if (movementTimer >= movementWait)
		{
			movementTimer = 0;
		}
	}

private:
	void DeathCheck()
	{
		if (currentTurn < 3)
		{
			currentTurn++;
			return;
		}

		if (snakeList[0].x >= 20 ||
			snakeList[0].x < 0 ||
			snakeList[0].y >= 20 ||
			snakeList[0].y < 0)
		{
			alive = false;
		}

		for (size_t i = 1; i < snakeList.size(); i++)
		{
			if (snakeList[0].x == snakeList[i].x &&
				snakeList[0].y == snakeList[i].y)
			{
				alive = false;
			}
		}
	}

	void getPlayerInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			snakeList[0].directionY = 1;
			snakeList[0].directionX = 0;

			if (snakeList[0].y + 1 >= 20)
			{
				snakeList[0].directionY = 0;
			}
			
			hasStarted = true;
		}

		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			snakeList[0].directionY = -1;
			snakeList[0].directionX = 0;

			if (snakeList[0].y - 1 < 0)
			{
				snakeList[0].directionY = 0;
			}

			hasStarted = true;
		}

		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			snakeList[0].directionX = -1;
			snakeList[0].directionY = 0;

			if (snakeList[0].x - 1 < 0)
			{
				snakeList[0].directionX = 0;
			}

			hasStarted = true;
		}

		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			snakeList[0].directionX = 1;
			snakeList[0].directionY = 0;

			if (snakeList[0].x + 1 >= 20)
			{
				snakeList[0].directionX = 0;
			}

			hasStarted = true;
		}
	}
};