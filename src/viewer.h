#ifndef VIEWER_H
#define VIEWER_H

#include <mujoco/mujoco.h>

namespace mujoco_multiview
{
    void launch_viewers(mjModel *model, mjData *data, int instances);
}

#endif // VIEWER_H
