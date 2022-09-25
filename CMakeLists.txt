cmake_minimum_required (VERSION 3.5)

project (ConnectFour C)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.c")

add_executable (ConnectFour ${source_files}   "include/board.h" "src/board.c")
