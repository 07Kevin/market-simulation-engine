cmake_minimum_required(VERSION 3.20)
project(cli01)

# Fetch ftxui
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9
)

FetchContent_MakeAvailable(ftxui)

# Create executable
add_executable(cli01 cli01.cpp)

# Link libraries
target_link_libraries(cli01
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)