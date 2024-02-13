cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(boost-util-examples)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(BoostUtility)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(1-base-from-member)
