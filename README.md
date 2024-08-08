# VerySickTissueMaker

## src directory
Source contains the main driver code for this program. 
E.g.   Application.h   <- - +  - - - Window.h
                            |   
                            +  - - - Renderer.h

## 3rdparty
Contains 3rd party library and files.
So far this includes:
- __glad__ : Load opengl function pointers 
- __glfw__ : For managing cross-platform windows
- __spdlog__ : A fast logging library

## assets
Contains the files, objects and other assets for rendering.
As well the subdirectory __shaders__ which contain the opengl shaders used in the renderer.h class
