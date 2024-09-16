#------section start: basic project setup------#
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (BadEngineCore)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
#------section end: basic project setup------#

#------section start: build engine------#
file (GLOB SOURCE_FILES CMAKE_CONFIGURE_DEPENDS
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
				src/Renderer/Buffers/*.h
				src/Renderer/Buffers/*.cpp
				src/Renderer/Camera/*.h
				src/Renderer/Camera/*.cpp
			src/ECSSystems/*.h
			src/ECSSystems/*.cpp
			src/ResourceLoader/*.h
			src/ResourceLoader/*.cpp
			src/Main/*.h
			src/Main/*.cpp
			src/UI/imgui/*.h
			src/UI/imgui/*.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

#set default build type to release if not provided
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#add RELEASE_WITH_DEBUG macro if compiling with RELEASE_WITH_DEBUG option
if(RELEASE_WITH_DEBUG)
    add_definitions(-DRELEASE_WITH_DEBUG)
endif()

#we precompile standard library headers
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
#------section end: build library------#

#------section start: build third party------# 
#disable building glfw docs, unit tests and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(THIRD_PARTY_PATH ${CMAKE_CURRENT_LIST_DIR}/3rdParty)

#add third party cmakes
find_package(OpenGL REQUIRED)
add_subdirectory(${THIRD_PARTY_PATH}/glfw)
add_subdirectory(${THIRD_PARTY_PATH}/glad)
add_subdirectory(${THIRD_PARTY_PATH}/spdlog)
add_subdirectory(${THIRD_PARTY_PATH}/glm)
add_subdirectory(${THIRD_PARTY_PATH}/assimp)
add_subdirectory(${THIRD_PARTY_PATH}/imgui)
add_subdirectory(${THIRD_PARTY_PATH}/entt)

#include the directories to resolve relative file references: "../../3rdparty/imgui" -> "3rdparty/imgui"
#includes used by engine and application
set(INTERNAL_AND_EXTERNAL_INCLUDES
    ${THIRD_PARTY_PATH}/glfw/include
    ${THIRD_PARTY_PATH}/glad/include
    ${THIRD_PARTY_PATH}/glm
	${THIRD_PARTY_PATH}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/build/3rdparty/assimp/include
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}
)

#includes only used by engine
set(INTERNAL_ONLY_INCLUDES
	${THIRD_PARTY_PATH}/imgui/backends
    ${THIRD_PARTY_PATH}/spdlog/include
    ${THIRD_PARTY_PATH}/stb
    ${THIRD_PARTY_PATH}/entt/src
	${THIRD_PARTY_PATH}/assimp/include
    ${ASSIMP_CONFIG_INCLUDE}
)

set(THIRD_PARTY_PATH ${CMAKE_CURRENT_LIST_DIR}/3rdParty)

#add the include directories
target_include_directories(${PROJECT_NAME} 
    PUBLIC  
        $<BUILD_INTERFACE:${INTERNAL_AND_EXTERNAL_INCLUDES}>  
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}> 
    PRIVATE  
        $<BUILD_INTERFACE:${INTERNAL_ONLY_INCLUDES}>
)

#------section end: build third party------# 

##link 3rd party
target_link_libraries(${PROJECT_NAME} PUBLIC
				${OPENGL_LIBRARIES}
				glad 
				spdlog 
				OpenGL::GL 
				glfw 
				assimp::assimp 
				imgui
				EnTT
)