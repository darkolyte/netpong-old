# Add executable for project
add_executable(${PROJECT_NAME})

# Include directories for our executable
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        {CMAKE_SOURCE_DIR}/inc/
        {CMAKE_SOURCE_DIR}/inc/Enet
)

# Source files for our executable
target_sources(
    ${PROJECT_NAME}
    PRIVATE
        NetPong.cpp
        Application.cpp
        Audio.cpp
        StateManager.cpp
        ExampleState.cpp
)

# Libraries to link to our executable
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        ExtLibs
)