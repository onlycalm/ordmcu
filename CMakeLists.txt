cmake_minimum_required(VERSION 3.16)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_PROJECT_NAME ordmcu)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_TOOLCHAIN_FILE "cmake/gcc-arm-none-eabi.cmake")

project(${CMAKE_PROJECT_NAME})

enable_language(C ASM)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(strtup)
add_subdirectory(core)
add_subdirectory(drv)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols.
    STM32F103xE
    USE_HAL_DRIVER
    HSE_VALUE=8000000
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    # Add user defined libraries.
    m
    c
    nosys
)

# 生成HEX和BIN文件
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generating HEX and BIN files"
)

# 显示内存使用情况
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
    COMMENT "Firmware size:"
)
