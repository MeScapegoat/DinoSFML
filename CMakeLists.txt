cmake_minimum_required(VERSION 3.22)
project(DinoSFML VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()

file(GLOB SOURCES
    ./*.h
    ./*.cpp
)


add_executable(DinoSFML ${SOURCES})

target_link_libraries(DinoSFML PRIVATE sfml-system)
target_link_libraries(DinoSFML PRIVATE sfml-window)
target_link_libraries(DinoSFML PRIVATE sfml-graphics)
target_link_libraries(DinoSFML PRIVATE sfml-audio)
target_link_libraries(DinoSFML PRIVATE sfml-network)

add_compile_definitions(SFML_STATIC)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
