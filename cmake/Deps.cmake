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
    set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
    set(SDL2_DISABLE_SDL2MAIN ON CACHE BOOL  "" FORCE)
    set(SDL2_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
    add_subdirectory(libs/SDL2)
endif ()