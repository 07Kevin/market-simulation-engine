cmake_minimum_required(VERSION 3.20)
project(tests)

# === Global Settings ===
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

include(include_external)
include(FetchContent)

# ================================================================
# 1. PRE-CONFIGURATION (Crucial: Must be BEFORE FetchContent)
# ================================================================
# This stops curl from bringing in 50 extra projects/tests
set(BUILD_CURL_EXE      OFF CACHE INTERNAL "")
set(BUILD_TESTING       OFF CACHE INTERNAL "")
set(BUILD_SHARED_LIBS   OFF CACHE INTERNAL "")
set(CURL_BUILD_TESTS    OFF CACHE INTERNAL "")
set(CURL_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(CURL_USE_LIBPSL     OFF CACHE INTERNAL "")
set(CMAKE_USE_LIBIDN2   OFF CACHE INTERNAL "")
set(CURL_USE_NGHTTP2    OFF CACHE INTERNAL "")
set(CURL_USE_ZSTD       OFF CACHE INTERNAL "")
set(CURL_USE_BROTLI     OFF CACHE INTERNAL "")

# This is the key line — tells curl to use Windows' built-in SSL
set(CURL_USE_SCHANNEL   ON  CACHE INTERNAL "")

# Disable protocols you don't need to speed up build & reduce noise
set(CURL_DISABLE_LDAP   ON CACHE INTERNAL "")
set(CURL_DISABLE_FTP    ON CACHE INTERNAL "")
set(CURL_DISABLE_SMTP   ON CACHE INTERNAL "")


# ================================================================
# 2. FETCH CURL
# ================================================================
FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG        curl-8_12_1
    GIT_SHALLOW    TRUE
)

# This command effectively does the "Populate" and "add_subdirectory" 
# logic for you in one clean step.
FetchContent_MakeAvailable(curl)

#find_package(CURL REQUIRED)

# ================================================================
# 3. YOUR EXECUTABLES
# ================================================================

# Common include path
set(EXTERNAL_INC ${CMAKE_SOURCE_DIR}/external)

# Main executable
add_executable(main "main.cpp")
target_include_directories(main PRIVATE ${EXTERNAL_INC})


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

target_include_directories(_TEST_curl PRIVATE
   ${CMAKE_SOURCE_DIR}/external 
)

# Link curl **AFTER** add_executable, not inside it
#target_link_libraries(_TEST_curl CURL::libcurl)


#target_include_directories(_TEST_curl PRIVATE
#   ${CMAKE_SOURCE_DIR}/external
#   
#)

# Link against the libcurl target created by FetchContent
target_link_libraries(_TEST_curl PRIVATE libcurl)
