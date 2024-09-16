cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
project (BEEditor)

add_subdirectory(../BadEngineCore out)
include_directories(../BadEngineCore/include)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} BadEngineCore)
