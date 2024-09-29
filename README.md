# OpenGL Graphics Project

This project is a C++ application that utilizes OpenGL for rendering graphics and ImGui for creating a user interface.

## Project Structure

The main components of the project include:

- `main.cpp`: The entry point of the application
- Various scene files (e.g., `scene_triangle.h`, `scene_square.h`, `scene_colored_triangle.h`, etc.)
- Utility files (`utils.h`, `resources.h`, etc.)
- ImGui integration (`imgui/imgui.h`)

## Dependencies

This project requires the following libraries:

- OpenGL
- GLEW
- ImGui

## Building the Project

The project uses a Makefile for compilation. To build the project, run: `make`

## Running the Application

After building, run the executable: `make run`

## Features

The application appears to support various rendering scenarios, including:

- Basic shapes (triangles, squares)
- Colored shapes
- Multiple VBOs (Vertex Buffer Objects)
- Shared VAOs (Vertex Array Objects)
- 3D objects (cubes)
- Transformations
 
