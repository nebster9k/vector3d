cmake_minimum_required(VERSION 3.0)

project(vector3d LANGUAGES CXX)

add_executable(vector3d vector3d.cpp vector3d.h test.cpp)
target_include_directories(vector3d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(external/Catch2)
target_link_libraries(vector3d Catch2::Catch2WithMain)

install(TARGETS vector3d
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
