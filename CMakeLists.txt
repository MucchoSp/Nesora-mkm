cmake_minimum_required(VERSION 3.5.0)
project(Nesora-mkm VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# cファイルをビルド対象に加える
file(GLOB_RECURSE NESORA_MAIN_SOURCES "src/Nesora/*.cpp")
add_library(nesora_main_lib STATIC ${NESORA_MAIN_SOURCES})
add_executable(main main.cpp)
target_link_libraries(main nesora_main_lib)

# C++の標準規格の指定
target_compile_features(nesora_main_lib PUBLIC cxx_std_17)
target_compile_features(main PUBLIC cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
