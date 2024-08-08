# Set which version of cmake we need, will throw an error if this check fails.
cmake_minimum_required(VERSION 3.16...3.23)

# Set which version of C++ we want to use
set(CMAKE_CXX_STANDARD 23)

# Set the project name. This will affect our output program -> "name".exe
project ("VerySickTissueMaker")

#set variables
set(GLFW_INCLUDES  "3rdParty/glfw/include")
set(GLAD_INCLUDES  "3rdParty/glad/include")
set(SPDLOG_INCLUDES  "3rdParty/spdlog/include")

if(RELEASE_WITH_DEBUG)
    add_definitions(-DRELEASE_WITH_DEBUG)
endif()

#	glfw
#disable unit tests
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#addsub dir
add_subdirectory("3rdParty/glfw")

#	opengl
#find opengl
find_package(OpenGL REQUIRED)

#	glad
add_subdirectory("3rdParty/glad")

#spdlog
add_subdirectory("3rdparty/spdlog")

#include the directories to resolve relative file references: "../../3rdparty/imgui" -> "3rdparty/imgui"
include_directories(${GLFW_INCLUDES})
include_directories(${GLAD_INCLUDES})
include_directories(${SPDLOG_INCLUDES})

#
#						end compile 3rdParty
#

#set includes for the tissue maker files
include_directories("src")
include_directories("3rdparty/glfw/include")

file (GLOB source_files CMAKE_CONFIGURE_DEPENDS
	*.h
	*.cpp
		src/*.h
		src/*.cpp
			src/util/*.h
			src/util/*.cpp
			src/window/*.h
			src/window/*.cpp
			src/Renderer/*.h
			src/Renderer/*.cpp

)

add_executable(${PROJECT_NAME} ${source_files})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glad spdlog OpenGL::GL glfw)