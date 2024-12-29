cmake_minimum_required(VERSION 3.5.0)
project(Nesora-mkm VERSION 0.1.0 LANGUAGES C CXX)

# Request the required wxWidgets libs
add_subdirectory(lib/wxWidgets)

include(CTest)
enable_testing()

# cファイルをビルド対象に加える
file(GLOB_RECURSE NESORA_MAIN_SOURCES "src/Nesora/*.cpp")
add_library(nesora_main_lib STATIC ${NESORA_MAIN_SOURCES})

file(GLOB_RECURSE NESORA_GUI_SOURCES "src/NesoraEditor/*.cpp")
add_library(nesora_gui_lib STATIC ${NESORA_GUI_SOURCES})
target_link_libraries(nesora_gui_lib wx::net wx::core wx::base)

add_executable(main src/main.cpp)
target_link_libraries(main nesora_main_lib)
target_link_libraries(main nesora_gui_lib)
target_link_libraries(main wx::net wx::core wx::base)

# C++の標準規格の指定
target_compile_features(nesora_main_lib PUBLIC cxx_std_17)
target_compile_features(nesora_gui_lib PUBLIC cxx_std_17)
target_compile_features(main PUBLIC cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
