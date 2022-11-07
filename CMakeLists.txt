# CMakeList.txt: проект CMake для hash_tablle_array; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("hash_tablle_array")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (hash_tablle_array "hash_tablle_array.cpp" "hash_tablle_array.h" "test.cpp")


