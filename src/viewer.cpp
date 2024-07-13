#include "viewer.h"
#include "window.h"

#include <vector>
#include <stdio.h>
#include <GLFW/glfw3.h>

namespace mujoco_multiview
{
    void launch_viewers(mjModel *model, mjData *data, int instances)
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

        // Create windows
        std::vector<std::unique_ptr<MujocoWindow>> windows;
        windows.reserve(instances);

        // Give incremental camera IDs, these have to be defined in the model's XML
        for (int cameraId = 0; cameraId < instances; cameraId++)
        {
            windows.push_back(std::make_unique<MujocoWindow>(cameraId, &opt, &scn));
        }

        // Load the window context with given model and data
        for (const auto &window : windows)
        {
            window->load(model, data);
        }

        // Render loop while no windows need closing
        while (
            std::all_of(windows.begin(), windows.end(),
                        [](const std::unique_ptr<MujocoWindow> &window)
                        { return !window->shouldClose(); }))
        {
            for (const auto &window : windows)
            {
                window->render();
            }
            glfwPollEvents();
        }

        // Deallocate
        mjv_freeScene(&scn);
        glfwTerminate();
    }
}