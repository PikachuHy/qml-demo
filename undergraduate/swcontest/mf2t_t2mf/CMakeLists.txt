cmake_minimum_required(VERSION 3.8)
project(mf2t_t2mf)

set(CMAKE_CXX_STANDARD 11)

add_library(midifile midifile.h midifile.c)
add_executable(mf2t version.h midifile.h mf2t.c)
add_executable(t2mf version.h midifile.h t2mflex.c t2mf.h t2mf.c)
target_link_libraries(mf2t midifile)
target_link_libraries(t2mf midifile)

set(CMAKE_INSTALL_PREFIX /usr)
install(TARGETS mf2t DESTINATION bin)
install(TARGETS t2mf DESTINATION bin)