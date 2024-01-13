#pragma once
#include <cstdlib> 
#include <iostream> 
#include <time.h> 
#include "Snake.h"

struct Apple
{
	int x, y;
};

class AppleManager
{
public:
	Apple apples[1];

	int applesCount = sizeof(apples) / sizeof(Apple);
	float appleColour[3] = {1.0f, 0.5f, 0.5f};

	Snake* player;

	AppleManager(Snake* passInPlayer)
	{
		player = passInPlayer;

		srand(time(0));

		for (size_t i = 0; i < applesCount; i++)
		{
			apples[i].x = rand() % 20;
			apples[i].y = rand() % 20;
		}
	}

	void Update()
	{
		for (size_t i = 0; i < applesCount; i++)
		{
			if (player->snakeList[0].x == apples[i].x && player->snakeList[0].y == apples[i].y)
			{
				player->toAddPart = true;

				apples[i].x = rand() % 20;
				apples[i].y = rand() % 20;
			}
		}
	}
};