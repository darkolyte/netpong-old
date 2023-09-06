# Do not build SDL tests 
set(SLD_TEST OFF CACHE BOOL "" FORCE)

# Add SDL directory
add_subdirectory(SDL)

# Add SDL image directory
add_subdirectory(SDL_image)

# Add SDL ttf directory
add_subdirectory(SDL_ttf)

# Interface library so our project links to everything SDL3 does
add_library(ExtLibs INTERFACE)
target_link_libraries(
    ExtLibs
    INTERFACE 
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)