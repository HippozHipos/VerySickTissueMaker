# Set which version of cmake we need, will throw an error if this check fails.
cmake_minimum_required(VERSION 3.16...3.23)

# Set which version of C++ we want to use
set(CMAKE_CXX_STANDARD 23)

# Set the project name. This will affect our output program -> "name".exe
project ("VerySickTissueMaker_Renderer")

file (GLOB source_files CMAKE_CONFIGURE_DEPENDS
	*.h
	*.cpp
		src/*.h
		src/*.cpp
			src/ECS/*.h
			src/ECS/*.cpp
			src/Diagnostics/*.h
			src/Diagnostics/*.cpp
			src/Input/*.h
			src/Input/*.cpp
			src/Window/*.h
			src/Window/*.cpp
			src/Renderer/*.h
			src/Renderer/*.cpp
				src/renderer/Buffers/*.h
				src/renderer/Buffers/*.cpp
				src/renderer/Camera/*.h
				src/renderer/Camera/*.cpp
			src/ECSSystems/*.h
			src/ECSSystems/*.cpp
			src/ResourceLoader/*.h
			src/ResourceLoader/*.cpp
			src/Main/*.h
			src/Main/*.cpp
			src/UI/imgui/*.h
			src/UI/imgui/*.cpp
)

add_library(${PROJECT_NAME} ${source_files})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
#
#						start compile 3rdParty
#

#set variables
set(GLFW_INCLUDES	"3rdParty/glfw/include")
set(GLAD_INCLUDES	"3rdParty/glad/include")
set(SPDLOG_INCLUDES  "3rdParty/spdlog/include")
set(GLM_INCLUDES	"3rdParty/glm")
set(STB_INCLUDES	"3rdParty/stb")
set(ASSIMP_INCLUDES	"3rdParty/assimp/include")
set(IMGUI_INCLUDES	"3rdParty/imgui")
set(IMGUI_BACKENDS_INCLUDES	"3rdParty/imgui/backends")
set(ENTT_INCLUDES	"3rdParty/entt/src")

if (Debug)
	set(ASSIMP_CONFIG_INCLUDE	"out/build/x64-Debug/3rdparty/assimp/include")
endif()
if (Release)
	set(ASSIMP_CONFIG_INCLUDE	"out/build/x64-Release/3rdparty/assimp/include")
endif()
if (RELEASE_WITH_DEBUG)
	set(ASSIMP_CONFIG_INCLUDE	"out/build/x64-ReleaseWithDebug/3rdparty/assimp/include")
endif()

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

#	spdlog
add_subdirectory("3rdParty/spdlog")

#	glm
add_subdirectory("3rdParty/glm")

#	assimp
add_subdirectory("3rdParty/assimp")

#	imgui
add_subdirectory("3rdParty/imgui")

#	entt
add_subdirectory("3rdParty/entt")

#include the directories to resolve relative file references: "../../3rdparty/imgui" -> "3rdparty/imgui"
set(INTERNAL_AND_EXTERNAL_INCLUDES
    ${GLFW_INCLUDES}
    ${GLAD_INCLUDES}
    ${GLM_INCLUDES}
	${IMGUI_INCLUDES}
    "include"
    "src"
    "./"
)
set(INTERNAL_ONLY_INCLUDES
    ${SPDLOG_INCLUDES}
    ${STB_INCLUDES}
    ${ENTT_INCLUDES}
	${ASSIMP_INCLUDES}
    ${ASSIMP_CONFIG_INCLUDE}
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${INTERNAL_AND_EXTERNAL_INCLUDES}
	PRIVATE
        ${INTERNAL_ONLY_INCLUDES}
)

#questionable shenanigans but i really dont feel like giving a single fuck rn 
#(its to make these includes accessible to VerySickTissueMaker_Application)
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_include_directories(${PROJECT_NAME} PUBLIC "./")

#
#						end compile 3rdParty
#


target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
				glad 
				spdlog 
				OpenGL::GL 
				glfw 
				assimp::assimp 
				imgui
				EnTT
)