cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
project (BEEditor)

add_subdirectory(../BadEngineCore out)
include_directories(../BadEngineCore/include
	${CMAKE_CURRENT_LIST_DIR}/src)

file (GLOB SOURCE_FILES CMAKE_CONFIGURE_DEPENDS
	src/*.h
	src/*.cpp
		src/EditorMainUIElements/*.h
		src/EditorMainUIElements/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} BadEngineCore)
