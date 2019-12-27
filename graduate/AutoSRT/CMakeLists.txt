cmake_minimum_required(VERSION 3.5)

project(soa-service-composition LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
include_directories(3rd_part/aliyun-oss-cpp-sdk/sdk/include)
set(CMAKE_PREFIX_PATH "/Users/pikachu/Qt5.14.0/5.14.0/clang_64")
find_package(Qt5
    COMPONENTS
    Widgets LinguistTools Network
    Multimedia MultimediaWidgets
    REQUIRED)

set(TS_FILES soa-service-composition_zh_CN.ts)

#add_subdirectory(3rdpart)
add_subdirectory(3rd_part/libQtQiniuSdk)
include_directories(3rd_part/libQtQiniuSdk/lib)
add_subdirectory(demo)
set(SRCS

        main.cpp
        mainwindow.cpp
        mainwindow.h
        previewwidget.cpp previewwidget.h
        videoinputwidget.cpp videoinputwidget.h
        serviceprogress.cpp serviceprogress.h
        util.cpp util.h http.cpp http.h)
if(ANDROID)
  add_library(soa-service-composition SHARED
          ${SRCS}
    ${TS_FILES}
  )
else()
  add_executable(soa-service-composition
          ${SRCS}
    ${TS_FILES}
  )
endif()
target_link_libraries(soa-service-composition
    PRIVATE
    Qt5::Widgets Qt5::Network
    Qt5::Multimedia Qt5::MultimediaWidgets
        QtQiniu
    )

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
