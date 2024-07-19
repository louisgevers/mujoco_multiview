#include "window.h"

#include <sstream>

constexpr int LABEL_WIDTH = 640;
constexpr int LABEL_HEIGHT = 128;
constexpr int LABEL_OFFSET = 24;

namespace mujoco_multiview
{
    MujocoWindow::MujocoWindow(int cameraId, mjvOption *options, mjvScene *scene, GLFWmonitor *monitor, bool fullscreen)
    {
        mOptions = options;
        mScene = scene;

        std::stringstream title;
        title << "MuJoCo MultiView - Viewer " << (cameraId + 1);

        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        GLFWmonitor *targetMonitor = fullscreen ? monitor : NULL;
        mWindow = glfwCreateWindow(mode->width, mode->height, title.str().c_str(), targetMonitor, NULL);
        if (!mWindow)
        {
            glfwTerminate();
            mju_error("Could not create window.");
        }

        // Use fixed camera from model
        mCamera.type = mjCAMERA_FIXED;
        mCamera.fixedcamid = cameraId;

        mjr_defaultContext(&mContext);

        glfwMakeContextCurrent(mWindow);
        glfwSwapInterval(1);
    };

    MujocoWindow::~MujocoWindow()
    {
        mjr_freeContext(&mContext);
        glfwDestroyWindow(mWindow);
    };

    void MujocoWindow::load(mjModel *model, mjData *data)
    {
        mModel = model;
        mData = data;
        glfwMakeContextCurrent(mWindow);
        mjr_makeContext(mModel, &mContext, mjFONTSCALE_150);
    };

    void MujocoWindow::render()
    {
        glfwMakeContextCurrent(mWindow);

        mjrRect viewport = {0, 0, 0, 0};
        glfwGetFramebufferSize(mWindow, &viewport.width, &viewport.height);

        if (mVisible)
        {
            mjv_updateScene(mModel, mData, mOptions, NULL, &mCamera, mjCAT_ALL, mScene);
            mjr_render(viewport, mScene, &mContext);
        }
        else
        {
            // Black screen
            mjr_rectangle(viewport, 0, 0, 0, 1);
        }

        // Optionally add a label on the top of the screen
        if (mLabel)
        {
            // Top of screen with offset
            const int bottom = viewport.height - LABEL_HEIGHT - LABEL_OFFSET;
            // Center of the screen
            const int left = (viewport.width / 2) - (LABEL_WIDTH / 2);

            mjrRect label_viewport{left, bottom, LABEL_WIDTH, LABEL_HEIGHT};
            mjr_label(label_viewport, mjFONT_BIG, mLabel->c_str(), 0, 0, 0, 0.6, mLabelRGB[0], mLabelRGB[1], mLabelRGB[2], &mContext);
        }

        glfwSwapBuffers(mWindow);
    };

    bool MujocoWindow::shouldClose() const
    {
        return glfwWindowShouldClose(mWindow);
    };
} // namespace mujoco_multiview
