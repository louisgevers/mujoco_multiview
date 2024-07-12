#include "viewer.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_bindings, m)
{
    m.attr("__name__") = "mujoco_multiview._bindings";
    m.doc() = "Python bindings test.";

    m.def("launch_passive", &mujoco_multiview::launch_passive, "Launch multi window viewer passively.");
}