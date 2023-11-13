
include(FetchContent)
if (${WIN32})
    add_subdirectory(libs/pthread-win32)
endif ()

# TODO: Find out how to set stuff for FetchContent projects

if (${GLFW_SUPPORT})
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw/
            GIT_TAG 3.3.8
    )
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_INSTALL OFF)
    FetchContent_MakeAvailable(glfw)
endif ()

if (${SDL2_SUPPORT})
    FetchContent_Declare(
            sdl2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL/
            GIT_TAG release-2.28.5
    )
    set(SDL2_DISABLE_SDL2MAIN ON CACHE BOOL "Disables SDL2's main" FORCE)
    set(SDL2_DISABLE_INSTALL ON CACHE BOOL "Disables SDL2's install" FORCE)
    FetchContent_MakeAvailable(sdl2)
endif ()