cmake_minimum_required(VERSION 3.16)
project(mujoco_multiview)

set(CMAKE_CXX_STANDARD 17)

#  1. Fetch the location of MuJoCo installed through pip
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)
set(MUJOCO_PYTHON_PATH ${Python3_SITELIB}/mujoco)

if(NOT EXISTS ${MUJOCO_PYTHON_PATH})
    message(FATAL_ERROR "Could not find MuJoCo. Make sure it is installed through pip (pip install mujoco), and that CMake is launched from your virtual environment.")
endif()

message(STATUS "Path to MuJoCo: ${MUJOCO_PYTHON_PATH}")

# 2. Create a MuJoCo library with the dynamic library
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    file(GLOB MUJOCO_LIBS ${MUJOCO_PYTHON_PATH}/*.dylib)
    add_library(mujoco SHARED IMPORTED)
    target_sources(mujoco INTERFACE ${MUJOCO_LIBS})
else()
    message(FATAL_ERROR "No support for OS ${CMAKE_SYSTEM_NAME}. Please implement linking to MuJoCo library if you want to use.")
endif()

#  Add the MuJoCo python bindings headers
#  The python package does not contain all the necessary and dependent headers, even if the symbols are there.
#  We include them here, but the symbols are in the library built from python.
#  This way we do not have to rebuilt entirety of MuJoCo but link to the dynamic library instead.
set(MUJOCO_INCLUDE ${CMAKE_SOURCE_DIR}/mujoco/include ${CMAKE_SOURCE_DIR}/mujoco/python/mujoco ${CMAKE_SOURCE_DIR}/abseil)

#  Run the following script to generate the necessary files for pyhton bindings
execute_process(COMMAND ${CMAKE_SOURCE_DIR}/mujoco/python/make_sdist.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/mujoco/python)

#  3. Add the GLFW library
set(GLFW_PATH ${CMAKE_SOURCE_DIR}/glfw)
add_subdirectory(${GLFW_PATH})

#  4. Add pybind
find_package(pybind11 CONFIG REQUIRED)

#  5. Create the pybind module with dependencies
file(GLOB BINDING_SOURCES ${CMAKE_SOURCE_DIR}/src/*cpp)
pybind11_add_module(_bindings ${BINDING_SOURCES})
target_link_libraries(_bindings INTERFACE mujoco PRIVATE glfw)
target_include_directories(_bindings PRIVATE ${CMAKE_SOURCE_DIR}/src ${GLFW_PATH}/include ${MUJOCO_INCLUDE})

#  6. Compile the bindings
target_compile_definitions(_bindings PRIVATE)
install(TARGETS _bindings DESTINATION mujoco_multiview)