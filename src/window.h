#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>

#include <optional>

namespace mujoco_multiview
{
    class MujocoWindow
    {
    public:
        explicit MujocoWindow(int cameraId, mjvOption *options, mjvScene *scene);
        ~MujocoWindow();
        void load(mjModel *model, mjData *data);
        void render();
        bool shouldClose() const;
        void setVisible(bool visible) { mVisible = visible; };
        void setLabel(std::optional<std::string> &label) { mLabel = label; };
        void setLabelColor(float r, float g, float b)
        {
            mLabelRGB[0] = r;
            mLabelRGB[1] = g;
            mLabelRGB[2] = b;
        };

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
        std::optional<std::string> mLabel;
        float mLabelRGB[3] = {1., 1., 1.};
        bool mVisible = true;
    };

}

#endif // WINDOW_H
