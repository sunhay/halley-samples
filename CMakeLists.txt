cmake_minimum_required (VERSION 3.0)

project(halley-samples)

set(HALLEY_PATH "" CACHE FILEPATH "Path to the Halley root")
set(HOTRELOAD 1 CACHE BOOL "Sets whether to hot-reload this project")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HALLEY_PATH}/cmake/")
include(HalleyProject)

add_subdirectory(samples)
