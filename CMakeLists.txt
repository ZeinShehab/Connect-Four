cmake_minimum_required (VERSION 3.5)

project (ConnectFour C)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")
set (include_dir "${PROJECT_SOURCE_DIR}/include/")
set (test_dir "${PROJECT_SOURCE_DIR}/tests/")

file (GLOB source_files "${source_dir}/*.c")
file (GLOB include_files "${include_dir}/*.h")
file (GLOB test_files "${test_dir}/*")


add_executable (ConnectFour ${source_files}  ${include_files} ${test_files})
