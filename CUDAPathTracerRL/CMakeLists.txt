cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(PathTracer_CUDA LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 11)

set(
        INCLUDE_DIRS

        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(
        HEADER_FILES
        
        ${CMAKE_CURRENT_SOURCE_DIR}/include/camera.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/camera_gpu.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/color.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cuda_utils.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cudaHeaders.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cudaMain.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cutil_math.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gl_utils.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/lightsource.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/material.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/material_functions.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/object.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/pathtracer_params.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/pointlightsource.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/quadric.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ray.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ray_gpu.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/renderengine.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/renderengine_gpu.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/rl_helper_functions.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/scene_helper.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/shader_utils.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sphere.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/sphere_gpu.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/structs.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/triangle.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/vector3D.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/world.h 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/world_gpu.h
)

set(
        SOURCE_FILES

        ${CMAKE_CURRENT_SOURCE_DIR}/src/camera.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/cudaMain.cu 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dummy.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl_utils.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/material.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/quadric.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ray.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/renderengine.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/renderengine_gpu.cu 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shader_utils.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sphere.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector3D.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/world.cpp
)
add_library(cuda_base
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )
target_compile_features(cuda_base PUBLIC cxx_std_11)
set_target_properties(cuda_base
        PROPERTIES 
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON
        )

find_package(OpenGL REQUIRED)
add_subdirectory (external)
include_directories(
        external/glfw-3.1.2/include/
        external/glew-2.2.0/include/
        external/glm-0.9.7.1/
        .
)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.2.0)
set(CMAKE_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.2.0/lib/Release/x64)
find_package(GLEW REQUIRED)

set(OPENGL_RELATED_LIBS
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARIES}
        )
add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -D_CRT_SECURE_NO_WARNINGS
)

#set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -gencode arch=compute_90, code=[sm_90,compute_90]")

include_directories(${INCLUDE_DIRS})

add_executable(PathTracer_CUDA ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set_target_properties(PathTracer_CUDA
        PROPERTIES
            CUDA_SEPARABLE_COMPILATION ON
            CUDA_RESOLVE_DEVICE_SYMBOLS ON
    )

target_link_libraries(PathTracer_CUDA cuda_base ${OPENGL_RELATED_LIBS})
