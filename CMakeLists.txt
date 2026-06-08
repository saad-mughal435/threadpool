cmake_minimum_required(VERSION 3.16)
project(threadpool VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# ---- header-only library --------------------------------------------------
add_library(threadpool INTERFACE)
target_include_directories(threadpool INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(threadpool INTERFACE cxx_std_17)

find_package(Threads REQUIRED)
target_link_libraries(threadpool INTERFACE Threads::Threads)

# ---- demo -----------------------------------------------------------------
add_executable(tp_demo apps/demo.cpp)
target_link_libraries(tp_demo PRIVATE threadpool)
if(NOT MSVC)
  target_compile_options(tp_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ---- tests ----------------------------------------------------------------
option(TP_BUILD_TESTS "Build unit tests" ON)
if(TP_BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
  )
  FetchContent_MakeAvailable(Catch2)

  add_executable(tp_tests tests/thread_pool_tests.cpp)
  target_link_libraries(tp_tests PRIVATE threadpool Catch2::Catch2WithMain)

  enable_testing()
  add_test(NAME unit COMMAND tp_tests)
endif()
