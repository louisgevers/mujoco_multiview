#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"

#include <mujoco/mujoco.h>
#include <vector>
#include <optional>
#include <memory>

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

        // Window rendering hooks
        void setRenderVisible(int id, bool visible);
        void setLabel(int id, std::optional<std::string> &label);
        void setLabelColor(int id, float r, float g, float b);

    private:
        mjvOption mOption;
        mjvScene mScene;
        std::vector<std::unique_ptr<MujocoWindow>> mWindows;
        bool mRunning;
    };
}

#endif // APPLICATION_H
