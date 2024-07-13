#include "window.h"

namespace mujoco_multiview
{
    MujocoWindow::MujocoWindow(mjvOption *options, mjvScene *scene)
    {
        mOptions = options;
        mScene = scene;
        mWindow = glfwCreateWindow(640, 480, "MuJoCo MultiView", NULL, NULL);
        if (!mWindow)
        {
            glfwTerminate();
            mju_error("Could not create window.");
        }

        mjv_defaultCamera(&mCamera);
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

    bool MujocoWindow::shouldClose()
    {
        return glfwWindowShouldClose(mWindow);
    };
} // namespace mujoco_multiview
