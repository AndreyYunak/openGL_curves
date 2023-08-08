cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(PROJECT_NAME openGL_curves)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
	src/Renderer/shader.vs
	src/Renderer/shader.frag
	src/Renderer/stb_image.h
	src/camera.h
	external/3D_curves/3D_curves.h
	external/3D_curves/3D_curves.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm::glm)



