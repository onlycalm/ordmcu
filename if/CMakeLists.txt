if(NOT DEFINED MCU)
    message(FATAL_ERROR "MCU is not defined. Please define it to specify the microcontroller.")
endif()

if(MCU MATCHES "^(stm32)([a-z]+[0-9])")
    set(VENDOR ${CMAKE_MATCH_1}) # 保存()内匹配的供应商前缀。
    set(SERIES ${CMAKE_MATCH_2}xx) # 保存()内匹配的系列前缀。追加后缀。
    message(STATUS "Detected MCU: ${MCU}, Vendor: ${VENDOR}, Series: ${SERIES}")
else()
    message(FATAL_ERROR "Unsupported MCU: ${MCU}.")
endif()

if(VENDOR STREQUAL "stm32")
    if(SERIES STREQUAL "f1xx")
        set(GPIO_SRC_DIR gpio/stm32/f1xx)
        set(CLK_SRC_DIR clk/stm32/f1xx)
        set(INTR_SRC_DIR intr/stm32/f1xx)
    else()
        message(FATAL_ERROR "Unsupported STM32 series: ${SERIES}.")
    endif()
else()
    message(FATAL_ERROR "Unsupported vendor: ${VENDOR}.")
endif()

set(COM_INC_DIR com)
set(GPIO_INC_DIR gpio)
set(CLK_INC_DIR clk)
set(INTR_INC_DIR intr)

file(GLOB GPIO_SRC_ALL
    ${COM_INC_DIR}/*.c
    ${GPIO_SRC_DIR}/*.c
    ${CLK_SRC_DIR}/*.c
    ${INTR_SRC_DIR}/*.c
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${GPIO_SRC_ALL})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${COM_INC_DIR}
    ${GPIO_INC_DIR}
    ${CLK_INC_DIR}
    ${INTR_INC_DIR}
)
