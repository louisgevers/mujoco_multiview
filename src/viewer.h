#ifndef VIEWER_H
#define VIEWER_H

#include <mujoco/mujoco.h>

namespace mujoco_multiview
{
    void launch_passive(mjModel* model, mjData* data);
}

#endif // VIEWER_H
