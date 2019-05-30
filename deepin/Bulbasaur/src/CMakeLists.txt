cmake_minimum_required(VERSION 3.7)
set(TARGET bulbasaur)
project(${TARGET}
        VERSION 1.0.0
        DESCRIPTION "TreeSize for Deepin, Quickly Scan Directory Sizes and Find Space Hogs."
        )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS -O3)
    # generate qm files
    execute_process(COMMAND bash "translate_generation.sh"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
else ()
    set(CMAKE_CXX_COMPILER "clang++")
endif ()

# Find the library
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(DtkWidget REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")
add_executable(${TARGET} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})

target_include_directories(${TARGET} PUBLIC
        ${DtkWidget_INCLUDE_DIRS}
        ${Qt5Concurrent_INCLUDE_DIRS}
        )
target_link_libraries(${TARGET}
        ${DtkWidget_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5Concurrent_LIBRARIES}
        )

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${TARGET})
set(CPACK_DEBIAN_PACKAGE_NAME ${TARGET})
set(CPACK_DEBIAN_FILE_NAME "${TARGET}-${PROJECT_VERSION}-all.deb")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdtkwidget2")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "Optional")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "pikachuhy@163.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PikachuHy")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/PikachuHy/Bulbasaur")

set(CMAKE_INSTALL_PREFIX /usr)
install(TARGETS ${TARGET} DESTINATION bin)
install(FILES ../${TARGET}.desktop DESTINATION share/applications)
install(FILES ../${TARGET}.png DESTINATION share/icons)
# Install qm files
file(GLOB QM_FILES "translations/*.qm")
install(FILES ${QM_FILES} DESTINATION share/${TARGET}/translations)
include(CPack)