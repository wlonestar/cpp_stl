cmake_minimum_required(VERSION 3.22)
project(cpp_stl)

set(CMAKE_CXX_STANDARD 20)
option(USE_CLANG "build application with clang" ON)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

# because of network problem, I turn to use Boost.Test
# include(FetchContent)
# FetchContent_Declare(
#     googletest
#     # Specify the commit you depend on and update it regularly.
#     URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# integrate nlohmann json
# include(FetchContent)
# FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
# FetchContent_MakeAvailable(json)

# copy template html file
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/template
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
