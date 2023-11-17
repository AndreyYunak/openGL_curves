cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(imgui)


add_library(imgui STATIC 
	imgui.h
	imgui.cpp
	imgui_impl_opengl3.h
	imgui_impl_opengl3.cpp
	imgui_impl_glfw.h
	imgui_impl_glfw.cpp
	imconfig.h 
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_impl_opengl3_loader.h
	imgui_internal.h
	imgui_tables.cpp
	imgui_widgets.cpp
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h)
target_include_directories(imgui PUBLIC imgui/)

find_package(glfw)
target_link_libraries(imgui PRIVATE glfw)