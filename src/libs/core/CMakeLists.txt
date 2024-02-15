set(module_lib_name "libs-core")
set(module_target_name "rch-libs-core")
set(module_target_alias "rch::libs-core")
set(lib_type STATIC)

set(source_list
"edge.cpp"
"edge.h"
"functions.cpp"
"functions.h"
"point.cpp"
"point.h"
"two_vertices.cpp"
"two_vertices.h")

add_library(${module_target_name}
  ${lib_type}
  ${source_list})

add_library(${module_target_alias} ALIAS ${module_target_name})
target_include_directories(${module_target_name} PUBLIC "${PROJECT_SOURCE_DIR}/src")

set_target_properties(${module_target_name} PROPERTIES OUTPUT_NAME ${module_target_name})

add_subdirectory(pywrap)