cmake_minimum_required(VERSION 3.26)
project(megalib C)
set(PROJECT_VERSION 0.1.0)
set(API_VERSION 010)

set(CMAKE_C_STANDARD 11)


include(CMakeOptions.txt)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Deps)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(ML_IS_MAIN TRUE)
elseif ()
    set(ML_IS_MAIN FALSE)
endif ()

if (${WIN32})
    set(PLATFORM "WINDOWS")
elseif (${LINUX})
    set(PLATFORM "LINUX")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(PLATFORM "MACOS")
endif ()


set(public_headers
        src/megalib/megalib.h
        src/megalib/logging/logger.h
        src/megalib/logging/log.h
        src/megalib/os/window/window.h
        src/megalib/os/window/window.h
        src/megalib/os/thread/thread.h
        src/megalib/argvparse/argvparse.h
        src/megalib/datastructures/vector.h
        src/megalib/os/opengl/glad/gl.h
        src/megalib/os/opengl/glad/wgl.h
        src/megalib/os/opengl/KHR/khrplatform.h
)

set(sources
        src/megalib/argvparse/argvparse.c
        src/megalib/datastructures/vector.c
        src/megalib/logging/log.c
        src/megalib/logging/logger.c
        src/megalib/os/window/impl/win32_window.c
        src/megalib/os/opengl/gl.c
        src/megalib/os/opengl/wgl.c
        src/megalib/os/opengl/opengl.h
        src/megalib/os/opengl/impl/opengl_win32.c
)

add_library(megalib
        ${sources}
        ${public_headers})
set_target_properties(megalib PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(megalib PUBLIC ${PLATFORM})
set_target_properties(
        megalib PROPERTIES
        PUBLIC_HEADER "${public_headers}"
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${API_VERSION}"
)
target_include_directories(
        megalib
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src
        src
        src/megalib/os/opengl
        PRIVATE
        src
)

# Dependencies

if (${WIN32})
    target_link_libraries(megalib pthreadVC3)
elseif ()
    target_link_libraries(megalib pthread)
endif ()

add_subdirectory(examples)


# Shared/Static stuff

set(BUILD_SHARED_LIBS ${BUILD_SHARED})

if (${BUILD_SHARED_LIBS})
    MESSAGE(STATUS "Building megalib as a library")
    if (${WIN32})
        target_compile_definitions(megalib PRIVATE $<BUILD_INTERFACE:BUILD_LIBTYPE_SHARED> INTERFACE $<INSTALL_INTERFACE:USE_LIBTYPE_SHARED>)
        if (${MSVC})
            set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
        endif ()
    endif ()
elseif ()
    MESSAGE(STATUS "Building megalib as a static library")
    add_library(megalib_static ALIAS megalib)
endif ()


if (BUILD_SHARED_LIBS)
    set_property(TARGET megalib PROPERTY POSITION_INDEPENDENT_CODE ON)
endif ()

# Other stuff

file(COPY ${public_headers} DESTINATION "include")

if (DEFINED CMAKE_BUILD_TYPE)
    message(STATUS "Generated build type: ${CMAKE_BUILD_TYPE}")
else ()
    message(STATUS "Generated config types: ${CMAKE_CONFIGURATION_TYPES}")
endif ()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    if(ML_IS_MAIN)
        set(default_build_type Debug)
    else()
        message(WARNING "Default build type is not set (CMAKE_BUILD_TYPE)")
    endif()

    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")

    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
