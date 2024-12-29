# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES true)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/Users/wdeutsch/source/PicoTools/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(RGBTreeSample C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_options("-fmodules-ts")

# Add executable. Default name is the project name, version 0.1

add_executable(RGBTreeSample)

target_sources(RGBTreeSample
  PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    Colours.cpp NamedColours.cpp RGBTreeMod.cpp
)

target_sources(RGBTreeSample PRIVATE
    pio_spi.cpp XmasTreeSample.cpp
)

pico_generate_pio_header(RGBTreeSample ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

pico_set_program_name(RGBTreeSample "RGBTreeSample")
pico_set_program_version(RGBTreeSample "0.1")

pico_enable_stdio_uart(RGBTreeSample 1)
pico_enable_stdio_usb(RGBTreeSample 0)

# Add the standard library to the build
target_link_libraries(RGBTreeSample
        pico_stdlib
        hardware_pio
        )

# Add the standard include files to the build
target_include_directories(RGBTreeSample PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(RGBTreeSample 
        hardware_timer
        hardware_clocks
        )

pico_add_extra_outputs(RGBTreeSample)
