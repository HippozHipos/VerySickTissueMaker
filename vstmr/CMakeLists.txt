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
			src/diagnostics/*.h
			src/diagnostics/*.cpp
			src/window/*.h
			src/window/*.cpp
			src/renderer/*.h
			src/renderer/*.cpp
				src/renderer/buffers/*.h
				src/renderer/buffers/*.cpp
				src/renderer/camera/*.h
				src/renderer/camera/*.cpp
			src/vstmr/*.h
			src/vstmr/*.cpp
			src/ui/imgui/*h
			src/ui/imgui/*cpp

)

add_library(${PROJECT_NAME} ${source_files} "src/renderer/buffers/FrameBuffer.h" "src/renderer/buffers/FrameBuffer.cpp" "src/renderer/buffers/RenderBuffer.h" "src/renderer/buffers/RenderBuffer.cpp")

#set variables
set(GLFW_INCLUDES	"3rdParty/glfw/include")
set(GLAD_INCLUDES	"3rdParty/glad/include")
set(SPDLOG_INCLUDES  "3rdParty/spdlog/include")
set(GLM_INCLUDES	"3rdParty/glm")
set(STB_INCLUDES	"3rdParty/stb")
set(ASSIMP_INCLUDES	"3rdParty/assimp/include")
set(IMGUI_INCLUDES	"3rdParty/imgui")
set(IMGUI_BACKENDS_INCLUDES	"3rdParty/imgui/backends")

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

#	assimp
add_subdirectory("3rdParty/imgui")

#include the directories to resolve relative file references: "../../3rdparty/imgui" -> "3rdparty/imgui"
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SPDLOG_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${STB_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${ASSIMP_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${ASSIMP_CONFIG_INCLUDE})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_INCLUDES})

#questionable shenanigans but i really dont feel like giving a single fuck rn 
#(its to make these includes accessible to VerySickTissueMaker_Application)
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_include_directories(${PROJECT_NAME} PUBLIC "./")

#
#						end compile 3rdParty
#

#set includes for the tissue maker files


target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
				glad 
				spdlog 
				OpenGL::GL 
				glfw 
				assimp::assimp 
				imgui)