cmake_minimum_required(VERSION 3.9)

project(QtQiniuSdk
        VERSION 1.0.0
        LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build ${PROJECT_NAME} as a shared library" OFF)
option(USE_CONAN "Use C++ Package Manager Conan" ON)

set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib
        CACHE PATH "Installation directory for libraries")
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include
        CACHE PATH "Installation directory for headers")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5Core 5.5)
find_package(Qt5Network 5.5)
find_package(PkgConfig)

if(BUILD_SHARED_LIBS)
    add_definitions(-DQSS_LIBRARY)
else()
    add_definitions(-DQSS_STATIC)
endif()


add_subdirectory(lib)
add_subdirectory(demo)
find_package(Qt5Test)
if (Qt5Test_FOUND)
    # enable_testing() has to be in the root CMakeLists.txt, see https://cmake.org/pipermail/cmake/2010-November/040725.html
    enable_testing()
    add_subdirectory(test)
endif()
