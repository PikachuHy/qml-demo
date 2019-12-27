cmake_minimum_required(VERSION 3.5)

project(Snake LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.14.0\\5.14.0\\mingw73_64")
set(CMAKE_PREFIX_PATH "/Users/pikachu/Qt5.14.0/5.14.0/clang_64")
# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(Snake SHARED
    main.cpp
    widget.cpp
    widget.h
  )
else()
  add_executable(Snake
    main.cpp
    widget.cpp
    widget.h
    qrc.qrc
  )
endif()

target_link_libraries(Snake PRIVATE Qt5::Widgets)
