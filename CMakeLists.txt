cmake_minimum_required(VERSION 3.16)
project(glfw_app LANGUAGES C CXX)

set(THIRD_PARTY_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(THIRD_PARTY_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC "${THIRD_PARTY_INCLUDE_DIR}")
target_compile_features(glad PRIVATE c_std_99)

find_library(GLFW3_LIB
  NAMES glfw3 libglfw3 glfw3dll libglfw3dll
  PATHS "${THIRD_PARTY_LIB_DIR}"
  NO_DEFAULT_PATH
)
if (NOT GLFW3_LIB)
  message(FATAL_ERROR "Could not find GLFW library in ${THIRD_PARTY_LIB_DIR}")
endif()

add_executable(glfw_app src/main.cpp)
target_compile_features(glfw_app PRIVATE cxx_std_17)
target_include_directories(glfw_app PRIVATE "${THIRD_PARTY_INCLUDE_DIR}")
target_link_libraries(glfw_app PRIVATE glad "${GLFW3_LIB}")

if (WIN32)
  target_link_libraries(glfw_app PRIVATE opengl32 gdi32 user32 shell32)
elseif(APPLE)
  target_link_libraries(glfw_app PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
  find_package(OpenGL REQUIRED)
  target_link_libraries(glfw_app PRIVATE OpenGL::GL pthread dl)
endif()
