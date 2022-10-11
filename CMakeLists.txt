cmake_minimum_required (VERSION 3.5)

project (ConnectFour C)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")
set (include_dir "${PROJECT_SOURCE_DIR}/include/")

file (GLOB source_files "${source_dir}/*.c")
file (GLOB include_files "${include_dir}/*.h")


add_executable (ConnectFour ${source_files}  ${include_files} "tests/tests.c"  "tests/boardTests.c" "tests/gameTests.c"  "tests/gameTests.h" "tests/boardTests.h" "tests/tests.h" "include/console.h" "src/console.c")
