cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(PROJECT_NAME openGL_curves)
project(${PROJECT_NAME})


add_executable(${PROJECT_NAME} 
	src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
	src/Renderer/Shader/shader.vs
	src/Renderer/Shader/shader.frag
	src/Renderer/stb_image.h
	src/camera.h
	external/3D_curves/3D_curves.h
	external/3D_curves/3D_curves.cpp
)
target_compile_features(${PROJECT_NAME}  PUBLIC cxx_std_17)

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

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
						COMMAND ${CMAKE_COMMAND} -E copy_directory
						${CMAKE_SOURCE_DIR}/src/Renderer/Shader $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shader)


