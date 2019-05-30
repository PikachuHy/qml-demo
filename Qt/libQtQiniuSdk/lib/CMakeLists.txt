set(TARGET "QtQiniu")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DQT_QINIU_SDK_VERSION="${PROJECT_VERSION}")
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")
file(GLOB QM_FILES "i18n/*.qm")
set(SOURCE_FILES ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES}
        QtQiniu)

set(HEADERS
        QtQiniu auth.h uploadmanager.h qiniu_global.h)


add_library(${TARGET} ${SOURCE_FILES})

target_include_directories(${TARGET} PRIVATE ${BOTAN_INCLUDE_DIRS})

set_target_properties(${TARGET} PROPERTIES VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(${TARGET}
        PUBLIC Qt5::Core
        PUBLIC Qt5::Network)

foreach(LIB Qt5Network Qt5Core)
    set(PRIVATE_LIBS "${PRIVATE_LIBS} -l${LIB}")
endforeach()
configure_file(QtQiniu.pc.in ${CMAKE_CURRENT_BINARY_DIR}/QtQiniu.pc
        @ONLY
        NEWLINE_STYLE UNIX)

install(TARGETS ${TARGET}
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
install(FILES ${HEADERS}
        DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtQiniu.pc
        DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)
