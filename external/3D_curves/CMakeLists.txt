cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(3D_curves)

add_library(3D_curves STATIC include/3D_curves/3D_curves.h 3D_curves.cpp)
target_include_directories(3D_curves PUBLIC include/)




# CMakeList.txt: проект CMake для 3D_curves; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
#add_executable (3D_curves "3D_curves.cpp" "3D_curves.h")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
 # set_property(TARGET 3D_curves PROPERTY CXX_STANDARD 20 COMPILE_FLAGS "/EHsc")
#endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
