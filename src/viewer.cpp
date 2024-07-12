#include "viewer.h"

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>

namespace mujoco_multiview
{
    void launch_passive()
    {
        printf("MuJoCo Version: %i\n", mjVERSION_HEADER);
        GLFWwindow *window;
        if (!glfwInit())
        {
            printf("Could not intialize glfw");
            return;
        }
        window = glfwCreateWindow(640, 480, "MuJoCo MultiView", NULL, NULL);
        if (!window)
        {
            printf("Could not create window");
            glfwTerminate();
            return;
        }
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}