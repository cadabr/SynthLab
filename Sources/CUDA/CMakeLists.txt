cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(PROJECT_NAME "SynthLabCuda")
message("Project name: " ${PROJECT_NAME})

if(NOT DEFINED ENV{CUDA_PATH})
    message(FATAL_ERROR "CUDA_PATH is not defined!")
endif()

project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CUDA CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)
set(SythLabCudaPATH ${${PROJECT_NAME}_BINARY_DIR}/${CMAKE_BUILD_TYPE_INIT} CACHE INTERNAL "")

set(
    SOURCES
        CudaHeader.cuh
        CudaSource.cu
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY IMPORTED_IMPLIB "${SythLabCudaPATH}/${PROJECT_NAME}.lib")

target_link_libraries("${PROJECT_NAME}" PRIVATE cudart)
