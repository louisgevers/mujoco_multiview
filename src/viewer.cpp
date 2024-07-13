#include "viewer.h"

#include <stdio.h>
#include <GLFW/glfw3.h>

namespace mujoco_multiview
{
    void launch_passive(mjModel* model, mjData* data)
    {
        mjvCamera cam;
        mjvOption opt;
        mjvScene scn;
        mjrContext con;

        // Initialize
        mjv_defaultOption(&opt);
        mjv_defaultCamera(&cam);
        mjv_defaultScene(&scn);
        mjr_defaultContext(&con);

        // Create scene 
        mjv_makeScene(model, &scn, 2000);

        GLFWwindow *window;
        if (!glfwInit())
        {
            mju_error("Could not initialize glfw.");
        }
        window = glfwCreateWindow(640, 480, "MuJoCo MultiView", NULL, NULL);
        if (!window)
        {

            glfwTerminate();
            mju_error("Could not create window.");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        // Make context
        mjr_makeContext(model, &con, mjFONTSCALE_150);

        while (!glfwWindowShouldClose(window))
        {
            mjrRect viewport = {0, 0, 0, 0};
            glfwGetFramebufferSize(window, &viewport.width, &viewport.height);

            mjv_updateScene(model, data, &opt, NULL, &cam, mjCAT_ALL, &scn);
            mjr_render(viewport, &scn, &con);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }


        mjv_freeScene(&scn);
        mjr_freeContext(&con);

        mj_deleteData(data);
        // mj_deleteModel(m); // I think we need to keep this, it will be freed from python

        glfwDestroyWindow(window);
        glfwTerminate();
    }
}