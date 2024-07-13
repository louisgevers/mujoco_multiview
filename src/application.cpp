#include "application.h"

#include <GLFW/glfw3.h>

namespace mujoco_multiview
{
    Application::Application(mjModel *model, mjData *data, int instances) : mOption(), mScene(), mWindows()
    {
        // Initialize
        mjv_defaultOption(&mOption);
        mjv_defaultScene(&mScene);

        // Visible flex edges
        mOption.flags[mjVIS_FLEXEDGE] = 1;

        // Allocate scene resources
        mjv_makeScene(model, &mScene, 2000);

        // Initialize glfw
        if (!glfwInit())
        {
            mju_error("Could not initialize glfw.");
        }

        // Create windows
        mWindows.reserve(instances);
        // Give incremental camera IDs, these have to be defined in the model's XML
        for (int cameraId = 0; cameraId < instances; cameraId++)
        {
            mWindows.push_back(std::make_unique<MujocoWindow>(cameraId, &mOption, &mScene));
        }

        // Load the window context with given model and data
        for (const auto &window : mWindows)
        {
            window->load(model, data);
        }
    }

    Application::~Application()
    {
        // Deallocate
        mjv_freeScene(&mScene);
        glfwTerminate();
    }

    void Application::renderLoop()
    {
        mRunning = true;
        while (shouldRun())
        {
            for (const auto &window : mWindows)
            {
                window->render();
            }
            glfwPollEvents();
        }
    }

    const bool Application::shouldRun()
    {
        bool windowsShouldClose = std::any_of(mWindows.begin(), mWindows.end(),
                                              [](const std::unique_ptr<MujocoWindow> &window)
                                              { return window->shouldClose(); });
        return !windowsShouldClose && mRunning;
    }

    void Application::sync()
    {
        // TODO locking and window sync
    }

    void Application::close()
    {
        // TODO locking
        mRunning = false;
    }
} // namespace mujoco_multiview
