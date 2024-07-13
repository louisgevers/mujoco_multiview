#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>

namespace mujoco_multiview
{
    class MujocoWindow
    {
    public:
        explicit MujocoWindow(mjvOption *options, mjvScene *scene);
        ~MujocoWindow();
        void load(mjModel *model, mjData *data);
        void render();
        bool shouldClose();

    private:
        // FIXME: get rid of raw pointers
        // Shared stuff
        mjModel *mModel;
        mjData *mData;
        mjvOption *mOptions;
        mjvScene *mScene;
        // Owned
        GLFWwindow *mWindow;
        mjrContext mContext;
        mjvCamera mCamera;
    };

}

#endif // WINDOW_H
