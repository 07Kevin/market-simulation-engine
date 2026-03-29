Place code here to try and test things out. This is a temporary things to test out code and see if it works. This is not meant to be a permanent place for code


*Using ftxui*
```
include(FetchContent)
 
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9  # Replace with a version, tag, or commit hash
)
 
FetchContent_MakeAvailable(ftxui)
 
add_executable(main main.cpp)
target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
```