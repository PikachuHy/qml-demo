set(TARGET "qiniu-sdk-demo")

set(SOURCE main.cpp)

add_executable(${TARGET} ${SOURCE})
link_directories(${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${TARGET} Qt5::Core Qt5::Network QtQiniu)
target_include_directories(${TARGET}
        PUBLIC ${PROJECT_SOURCE_DIR}/lib)

