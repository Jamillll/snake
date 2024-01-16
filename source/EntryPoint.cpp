#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "rendering/renderer.h"
#include "Logic/Grid.h"
#include "Logic/Snake.h"
#include "Logic/AppleManager.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return NULL;

    window = glfwCreateWindow(800, 800, "Snake", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return NULL;
    }

    Grid mainGrid;

    Renderer renderer(window);
    renderer.SetVertexDataPointer(mainGrid.cells, sizeof(Cell) * (mainGrid.axisLength * mainGrid.axisLength));
    renderer.SetIndexDataPointer(mainGrid.indices, (sizeof(unsigned int) * (mainGrid.axisLength * mainGrid.axisLength)) * 6);

    Snake player;
    AppleManager apples(&player);

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            player.SetupSnake();
        }

        mainGrid.Update();
        player.Update(window);
        apples.Update();

        for (size_t i = 0; i < player.snakeList.size(); i++)
        {
            if (player.alive == true)
            {
                mainGrid.SetCellColour(player.snakeList[i].x, player.snakeList[i].y, 0.1, 0.5, 0.1);
            }
            else
            {
                mainGrid.SetCellColour(player.snakeList[i].x, player.snakeList[i].y, 0.7f, 0.0f, 0.0f);
            }
        }

        for (size_t i = 0; i < apples.applesCount; i++)
        {
            mainGrid.SetCellColour(apples.apples[i].x, apples.apples[i].y, apples.appleColour[0], apples.appleColour[1], apples.appleColour[2]);
        }

        renderer.Draw();

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}