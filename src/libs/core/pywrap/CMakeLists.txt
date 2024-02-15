set(module_target_name "rch_cpp_gis_lib_core")

pybind11_add_module(${module_target_name} pywrap.cpp)

target_compile_definitions(${module_target_name} PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
target_include_directories(${module_target_name}
PUBLIC
  "${PROJECT_SOURCE_DIR}/src" 
PRIVATE
  ${PYBIND11_INCLUDE_DIRS})

target_link_libraries(${module_target_name}
  PUBLIC
    rch::libs-core)