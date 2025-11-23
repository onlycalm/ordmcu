cmake_minimum_required(VERSION 3.16)

# 使用C11标准编译C代码，必须支持C11，并且允许使用编译器的扩展功能。
set(CMAKE_C_STANDARD 11) # 指定使用C11标准。
set(CMAKE_C_STANDARD_REQUIRED ON) # 要求编译器必须支持`CMAKE_C_STANDARD` 指定的标准（这里是 C11）。
set(CMAKE_C_EXTENSIONS ON) # 允许使用编译器的GNU扩展（或 MSVC 等特定扩展）。

# 定义构建类型。
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_PROJECT_NAME ord32) # 设置工程名宏。

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE) # 在构建过程中生成一个名为 `compile_commands.json` 的文件，这个文件记录了每个源文件（如 `.c`, `.cpp`）的完整编译命令（包括编译器路径、宏定义、包含路径、编译选项等）。

# 设置工具链
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)

# 配置工程名，和支持语言，这里支持C和汇编ASM。
project(${CMAKE_PROJECT_NAME})
enable_language(C ASM)
# project(${CMAKE_PROJECT_NAME} LANGUAGES C ASM) # 和上面的配置等价。

add_executable(${CMAKE_PROJECT_NAME}) # 设置生成的可执行文件名，这里没有给出依赖的源文件列表。

# add_subdirectory(
#     # Add subdirectory.
# )

# 链接目录设置。
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths.
)

# target_link_directories(<target> <visibility> directory1 directory2 ...)
# - `<target>`：目标名称，通常是通过 `add_executable()` 或 `add_library()` 创建的。
# - `<visibility>`：控制该链接目录如何被传递：
#   - `PRIVATE`：仅用于当前目标，不对外暴露。
#   - `INTERFACE`：仅对依赖此目标的其他目标可见（适用于库）。
#   - `PUBLIC`：既用于自身，也传递给依赖者。

# 添加源文件。
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here.
    startup/startup_stm32f103xe.s

    # Core 源文件
    core/src/main.c
    core/src/stm32f1xx_it.c
    core/src/system_stm32f1xx.c
    core/src/stm32f1xx_hal_msp.c
    core/src/syscalls.c

    # HAL 库核心文件
    drv/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
    drv/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
    drv/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
    drv/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
    drv/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_dma.c
    drv/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_exti.c
)

# 包含路径设置。
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths.
    core/inc

    # CMSIS 头文件
    drv/CMSIS/Include
    drv/CMSIS/Device/ST/STM32F1xx/Include

    # HAL 库头文件
    drv/STM32F1xx_HAL_Driver/Inc
)

# 编译定义（宏定义）。
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols.
    STM32F103xE
    USE_HAL_DRIVER
    HSE_VALUE=8000000
)

# 添加链接库。
target_link_libraries(${CMAKE_PROJECT_NAME}
    # Add user defined libraries.
    m
    c
    nosys
)

# ========== 在这里添加生成HEX/BIN文件的命令 ==========
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
