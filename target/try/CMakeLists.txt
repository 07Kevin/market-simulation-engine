cmake_minimum_required(VERSION 3.14)
project(cli01)

# Using ftxui
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9  # Replace with a version, tag, or commit hash
)

FetchContent_MakeAvailable(ftxui)

# Add the cli01 subproject
add_subdirectory(cli01)