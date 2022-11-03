# CMakeList.txt : CMake project for ProjetSI, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ProjetSI")

# Add source to this project's executable.
add_executable (ProjetSI "src/ProjetSI.cpp" "include/ProjetSI.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ProjetSI PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
