#include "viewer.h"
#include <pybind11/pybind11.h>

#include <structs.h>

namespace py = pybind11;

namespace mujoco_multiview::python
{

    void launch_viewers_wrapper(py::object model_wrapper, py::object data_wrapper, int instances)
    {
        mjModel *model = model_wrapper.cast<mujoco::python::MjModelWrapper &>().get();
        mjData *data = data_wrapper.cast<mujoco::python::MjDataWrapper &>().get();
        mujoco_multiview::launch_viewers(model, data, instances);
    }

    PYBIND11_MODULE(_bindings, m)
    {
        m.attr("__name__") = "mujoco_multiview._bindings";
        m.doc() = "Python bindings test.";

        m.def("launch_viewers", &launch_viewers_wrapper, py::call_guard<py::gil_scoped_release>(), "Launch multi window viewer passively.");
    }
}
