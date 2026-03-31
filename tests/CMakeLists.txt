# CMakeList.txt : CMake project for testcmake, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.20)
include(include_external)

# Add source to this project's executable.

# Main executable file
add_executable (main 
   "main.cpp"
   #${CMAKE_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp
)

target_include_directories(main PRIVATE
   ${CMAKE_SOURCE_DIR}/external
)

# TEST_json executable file
add_executable (TEST_json 
   "TEST_json.cpp"
   ${CMAKE_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp
)

target_include_directories(TEST_json PRIVATE
   ${CMAKE_SOURCE_DIR}/external
   
)

# TEST_curl executable file
add_executable (TEST_curl 
   "TEST_curl.cpp"
   ${CMAKE_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp
)

target_include_directories(TEST_curl PRIVATE
   ${CMAKE_SOURCE_DIR}/external
   
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
