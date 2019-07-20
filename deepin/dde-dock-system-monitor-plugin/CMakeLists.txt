cmake_minimum_required(VERSION 3.9.5)

# 使用 set 命令设置一个变量
set(PLUGIN_NAME "system-monitor")

# 设置项目名称
project(${PLUGIN_NAME}
        VERSION 1.0.0
        DESCRIPTION "a simple system monitor plugin for dde dock"
        )
set(CMAKE_CXX_STANDARD 17)
option(Debug "Debug plugin" OFF)
if (Debug)
    add_definitions(-DDEBUG)
endif()
# 启用 qt moc 的支持
set(CMAKE_AUTOMOC ON)
# 启用 qrc 资源文件的支持
set(CMAKE_AUTORCC ON)

add_subdirectory(src)
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "dde-dock-${PLUGIN_NAME}-plugin")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PikachuHy")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "procps")
set(CPACK_DEBIAN_FILE_NAME ${PROJECT_NAME}_${PROJECT_VERSION}.deb)
include(CPack)