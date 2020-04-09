
enable_testing()
find_package(GTest REQUIRED)
file (GLOB_RECURSE TEST_SRC_FILES "*.cpp")

# from list of files we'll create tests test_name.cpp -> test_name
foreach (_test_file ${TEST_SRC_FILES})
  get_filename_component (_test_name ${_test_file} NAME_WE)
  add_executable (${_test_name}
    ${_test_file}
  )
  target_include_directories(${_test_name} PRIVATE ../src)
  target_link_libraries (${_test_name}
    pascal-interpreter_body
    GTest::GTest GTest::Main
  )
  add_test (${_test_name} ${_test_name})
endforeach ()