set(module_lib_name "libs-triangulation")
set(module_target_name "rch-libs-triangulation")
set(module_target_alias "rch::libs-triangulation")
set(lib_type STATIC)

set(source_list
  "triangulation.cpp"
  "triangulation.h")

add_library(${module_target_name}
  ${lib_type}
  ${source_list})

add_library(${module_target_alias} ALIAS ${module_target_name})
target_include_directories(${module_target_name} PUBLIC "${PROJECT_SOURCE_DIR}/src")

target_link_libraries(${module_target_name} 
  PUBLIC 
    rch::libs-core)

set_target_properties(${module_target_name} PROPERTIES OUTPUT_NAME ${module_target_name})
