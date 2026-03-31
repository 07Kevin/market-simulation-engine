# CMakeList.txt : CMake project for testcmake, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.20)
project(tests)

# === Enable C++20 for the entire project ===
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)   # optional but recommended (disables GNU extensions)

include(include_external)
include(FetchContent)


# ================================================================
# Fetch and configure curl
# ================================================================
FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG        curl-8_12_1
    GIT_SHALLOW    TRUE
)

# Disable everything that causes problems with FetchContent on Windows
set(BUILD_TESTING          OFF CACHE INTERNAL "")
set(CURL_BUILD_TESTS       OFF CACHE INTERNAL "")
set(CURL_BUILD_EXAMPLES    OFF CACHE INTERNAL "")
set(CURL_BUILD_TOOLS       OFF CACHE INTERNAL "")
set(BUILD_CURL_EXE         OFF CACHE INTERNAL "")

set(CURL_USE_LIBPSL        OFF CACHE INTERNAL "")
set(CMAKE_USE_LIBIDN2      OFF CACHE INTERNAL "")
set(CURL_USE_NGHTTP2       OFF CACHE INTERNAL "")
set(CURL_USE_ZSTD          OFF CACHE INTERNAL "")
set(CURL_USE_BROTLI        OFF CACHE INTERNAL "")

# Optional: build curl as static library (recommended with FetchContent)
set(BUILD_SHARED_LIBS      OFF CACHE INTERNAL "")

# === THIS IS THE IMPORTANT CHANGE ===
FetchContent_GetProperties(curl)
if(NOT curl_POPULATED)
    FetchContent_Populate(curl)
    add_subdirectory(${curl_SOURCE_DIR} ${curl_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
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
add_executable (_TEST_curl 
   "TEST_curl.cpp"
   ${CMAKE_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp

)

# Link curl **AFTER** add_executable, not inside it
target_link_libraries(_TEST_curl PRIVATE libcurl)


target_include_directories(_TEST_curl PRIVATE
   ${CMAKE_SOURCE_DIR}/external
   
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
