#include "window.h"

#include <sstream>

namespace mujoco_multiview
{
    MujocoWindow::MujocoWindow(int cameraId, mjvOption *options, mjvScene *scene)
    {
        mOptions = options;
        mScene = scene;

        std::stringstream title;
        title << "MuJoCo MultiView - Viewer " << (cameraId + 1);

        mWindow = glfwCreateWindow(640, 480, title.str().c_str(), NULL, NULL);
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

        mjv_updateScene(mModel, mData, mOptions, NULL, &mCamera, mjCAT_ALL, mScene);
        mjr_render(viewport, mScene, &mContext);

        glfwSwapBuffers(mWindow);
    };

    bool MujocoWindow::shouldClose() const
    {
        return glfwWindowShouldClose(mWindow);
    };
} // namespace mujoco_multiview
