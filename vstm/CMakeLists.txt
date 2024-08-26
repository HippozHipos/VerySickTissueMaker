cmake_minimum_required(VERSION 3.16...3.23)
set(CMAKE_CXX_STANDARD 23)
project ("VerySickTissueMaker_Application")

include_directories("../vstmr/include")
add_subdirectory("../vstmr" "out")

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} VerySickTissueMaker_Renderer)
