cmake_minimum_required(VERSION 3.7)
set(TARGET_NAME krabby)
project(${TARGET_NAME}
        VERSION 1.1.0
        DESCRIPTION "a simple type application for deepin"
        )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")
if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

    # generate qm files
    execute_process(COMMAND bash "translate_generation.sh"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src)

else ()
    set(CMAKE_CXX_COMPILER "clang++")
endif ()
find_package(PkgConfig REQUIRED)
set(QT Core Gui Widgets Multimedia)
find_package(Qt5 REQUIRED ${QT})
pkg_check_modules(3rd_lib REQUIRED
        dtkwidget
        )
add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ${3rd_lib_INCLUDE_DIRS} )
target_link_libraries(${TARGET_NAME} ${3rd_lib_LIBRARIES} )
qt5_use_modules(${TARGET_NAME} ${QT})

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${TARGET_NAME})
set(CPACK_DEBIAN_PACKAGE_NAME ${TARGET_NAME})
set(CPACK_DEBIAN_FILE_NAME "${TARGET_NAME}-${PROJECT_VERSION}-all.deb")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdtkwidget2")
set(CPACK_DEBIAN_PACKAGE_SECTION "education")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "Optional")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "pikachuhy@163.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PikachuHy")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/PikachuHy/Krabby")

set(CMAKE_INSTALL_PREFIX /usr)
file(GLOB QM_FILES "translations/*.qm")
install(TARGETS ${TARGET_NAME} DESTINATION bin)
install(FILES ${QM_FILES} DESTINATION share/${TARGET_NAME}/translations)
install(FILES       "krabby.desktop"
        DESTINATION "share/applications")
install(FILES       "krabby.png"
        DESTINATION "share/icons")
include(CPack)