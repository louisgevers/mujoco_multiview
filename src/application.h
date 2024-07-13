#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"

#include <mujoco/mujoco.h>
#include <vector>

namespace mujoco_multiview
{
    class Application
    {
    public:
        Application(mjModel *model, mjData *data, int instances);
        ~Application();

        void renderLoop();
        const bool shouldRun();

        void sync();
        void close();

    private:
        mjvOption mOption;
        mjvScene mScene;
        std::vector<std::unique_ptr<MujocoWindow>> mWindows;
        bool mRunning;
    };
}

#endif // APPLICATION_H
