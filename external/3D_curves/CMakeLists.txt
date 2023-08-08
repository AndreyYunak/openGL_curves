# CMakeList.txt: проект CMake для 3D_curves; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (3D_curves "3D_curves.cpp" "3D_curves.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 3D_curves PROPERTY CXX_STANDARD 20 COMPILE_FLAGS "/EHsc")
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
