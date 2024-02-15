#include "libs/core/point.h"
#include "libs/reserves/mean_method.h"
#include "libs/reserves/triangles_method.h"

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

PYBIND11_MODULE(rch_cpp_gis_lib_reserves, m)
{
  //   m.doc() = "optional module docstring";
  m.def("mean_method", &reserves::mean_method::calc_reserves);
  m.def("triangles_method", &reserves::triangles_method::calc_reserves);
}