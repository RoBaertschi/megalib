
include(FetchContent)
FetchContent_Declare(
        ptw
        GIT_REPOSITORY https://github.com/GerHobbelt/pthread-win32
        GIT_TAG version-3.1.0-release
)
FetchContent_GetProperties(ptw ptw_SOURCE_DIR)
message("${ptw_SOURCE_DIR}")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${ptw_SOURCE_DIR}/cmake")
message(${CMAKE_MODULE_PATH})

FetchContent_MakeAvailable(ptw)