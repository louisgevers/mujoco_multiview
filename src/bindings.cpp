#include "application.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <structs.h>

namespace py = pybind11;

namespace mujoco_multiview::python
{

    class ApplicationWrapper
    {
    public:
        ApplicationWrapper(py::object model_wrapper, py::object data_wrapper, int instances)
            : mApplication(
                  std::make_unique<Application>(model_wrapper.cast<mujoco::python::MjModelWrapper &>().get(),
                                                data_wrapper.cast<mujoco::python::MjDataWrapper &>().get(),
                                                instances)) {}

        void renderLoop()
        {
            if (mApplication)
            {

                mApplication->renderLoop();
                mApplication.reset();
            }
            else
            {
                mju_error("Application is destroyed, cannot run render loop");
            }
        }

        const bool isRunning()
        {
            return mApplication != nullptr;
        }

        void sync()
        {
            if (mApplication)
            {
                mApplication->sync();
            }
        }

        void close()
        {
            if (mApplication)
            {
                mApplication->close();
            }
        }

        void setRenderVisible(int id, bool visible)
        {
            if (mApplication)
            {
                mApplication->setRenderVisible(id, visible);
            }
        }

        void setLabel(int id, std::optional<std::string> &label)
        {
            if (mApplication)
            {
                mApplication->setLabel(id, label);
            }
        }

        void setLabelColor(int id, float r, float g, float b)
        {
            if (mApplication)
            {
                mApplication->setLabelColor(id, r, g, b);
            }
        }

    private:
        std::unique_ptr<Application> mApplication;
    };

    PYBIND11_MODULE(_bindings, m)
    {
        m.attr("__name__") = "mujoco_multiview._bindings";
        m.doc() = "Python bindings test.";

        py::class_<ApplicationWrapper>(m, "Application")
            .def(py::init([](py::object m, py::object d, int instances)
                          { return std::make_unique<ApplicationWrapper>(m, d, instances); }))
            .def("render_loop", &ApplicationWrapper::renderLoop, py::call_guard<py::gil_scoped_release>())
            .def("is_running", &ApplicationWrapper::isRunning, py::call_guard<py::gil_scoped_release>())
            .def("sync", &ApplicationWrapper::sync, py::call_guard<py::gil_scoped_release>())
            .def("close", &ApplicationWrapper::close, py::call_guard<py::gil_scoped_release>())
            .def("set_render_visible", &ApplicationWrapper::setRenderVisible, py::call_guard<py::gil_scoped_release>())
            .def("set_label", &ApplicationWrapper::setLabel, py::call_guard<py::gil_scoped_release>())
            .def("set_label_color", &ApplicationWrapper::setLabelColor, py::call_guard<py::gil_scoped_release>());
    }
}
