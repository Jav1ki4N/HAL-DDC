cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME "HAL-DDC-F411CEU6")


# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C CXX ASM)

# Libraries 
file(GLOB HARDWARE
        #"${CMAKE_CURRENT_SOURCE_DIR}/Hardware.i4N/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Hardware.i4N/**/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Hardware.i4N/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Hardware.i4N/*.cpp"
)
file(GLOB SYSTEM
        #"${CMAKE_CURRENT_SOURCE_DIR}/System.i4N/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/System.i4N/*.cpp"
)
file(GLOB FREERTOS
        #"${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/**/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/**/**/*.c"
)
file(GLOB_RECURSE LVGL_SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL/*.c"        # nothing here normmally
    #"${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL/*.h"        # lvgl.h / lv_conf.h / lv_version.h
    "${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL/*.cpp"      # nothing here normally

    "${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL/**/*.c"     # lots of files here
    #"${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL/**/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL/**/*.cpp"
)

add_executable(${CMAKE_PROJECT_NAME}
               ${HARDWARE}
               ${SYSTEM}
               ${FREERTOS}
               ${LVGL_SRC}
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
        ${CMAKE_CURRENT_SOURCE_DIR}/Hardware.i4N
        ${CMAKE_CURRENT_SOURCE_DIR}/System.i4N
        ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares
        ${FREERTOS}
        ${LVGL_SRC}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
        ${CMAKE_CURRENT_SOURCE_DIR}/Hardware.i4N
        ${CMAKE_CURRENT_SOURCE_DIR}/Hardware.i4N/HAL-DDC-CORE
        ${CMAKE_CURRENT_SOURCE_DIR}/System.i4N
        ${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL
        ${CMAKE_CURRENT_SOURCE_DIR}/Middleware.i4N/LVGL/src
        ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source
        ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
        ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable
)
 
# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
        -u _printf_float ## Enable printing float via uart
)
