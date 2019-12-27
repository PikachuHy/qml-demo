add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE Qt5::Widgets)

add_executable(json json.cpp)
target_link_libraries(json PRIVATE Qt5::Widgets)

add_executable(alioss alioss.cpp)
target_link_directories(alioss
        PRIVATE ../3rd_part/aliyun-oss-cpp-sdk/build/lib)
target_link_libraries(alioss PRIVATE Qt5::Widgets
        alibabacloud-oss-cpp-sdk
        )