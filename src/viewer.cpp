#include "viewer.h"
#include "window.h"

#include <stdio.h>
#include <GLFW/glfw3.h>

namespace mujoco_multiview
{
    void launch_passive(mjModel* model, mjData* data)
    {
        mjvOption opt;
        mjvScene scn;

        // Initialize
        mjv_defaultOption(&opt);
        mjv_defaultScene(&scn);

        // Allocate scene resources
        mjv_makeScene(model, &scn, 2000);

        // Initialize glfw
        if (!glfwInit())
        {
            mju_error("Could not initialize glfw.");
        }

        // Create window
        MujocoWindow window{&opt, &scn};

        // Load the window context with given model and data
        window.load(model, data);

        // Render loop
        while (!window.shouldClose())
        {
            window.render();
            glfwPollEvents();
        }

        // Deallocate
        mjv_freeScene(&scn);
        glfwTerminate();
    }
}