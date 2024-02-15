#include "libs/core/functions.h"
#include "libs/core/point.h"

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

PYBIND11_MAKE_OPAQUE(std::vector<core::point>);

PYBIND11_MODULE(rch_cpp_gis_lib_core, m)
{
  m.doc() = "optional module docstring";

  py::class_<core::point>(m, "point")
    .def(py::init<double, double, double, double, double, double, double>())
    .def("get_x", &core::point::get_x)
    .def("get_y", &core::point::get_y)
    .def("get_z", &core::point::get_z)
    .def("get_z_roof", &core::point::get_z_roof)
    .def("get_thickness", &core::point::get_thickness)
    .def("get_content", &core::point::get_content)
    .def("get_density", &core::point::get_density);

  py::bind_vector<std::vector<core::point>>(m, "vector_point");
}