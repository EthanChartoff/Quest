# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# Project name
project(qc)

# Collect all source files using GLOB
file(GLOB_RECURSE SOURCE_FILES "src/*.c")
file(GLOB_RECURSE HEADER_FILES "src/include/*.h")

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE src/include)
# target_include_directories(${PROJECT_NAME} PRIVATE src/utils/lexer_DFA/include)

# Specify C standard
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

# Add any other necessary configurations or compiler flags here

# Copy the .dat files to build directory
# file(COPY ${CMAKE_SOURCE_DIR}/src/config/lexer_dfa.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# file(COPY ${CMAKE_SOURCE_DIR}/src/config/lexer_dfa_states.dat DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy the examples folder to build directory
file(COPY examples DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Install rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Copy resources to build directory
# file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Additional configurations for .gitignore, .vscode/settings.json, Makefile, etc.
# configure_file(${CMAKE_SOURCE_DIR}/.gitignore ${CMAKE_CURRENT_BINARY_DIR}/.gitignore COPYONLY)
# configure_file(${CMAKE_SOURCE_DIR}/.vscode/settings.json ${CMAKE_CURRENT_BINARY_DIR}/.vscode/settings.json COPYONLY)
# configure_file(${CMAKE_SOURCE_DIR}/Makefile ${CMAKE_CURRENT_BINARY_DIR}/Makefile COPYONLY)

