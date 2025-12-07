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
        set(DRV_DIR "stm32/f1xx/STM32F1xx_HAL_Driver")
        set(CMSIS_DIR "stm32/f1xx/CMSIS")
    else()
        message(FATAL_ERROR "Unsupported STM32 series: ${SERIES}.")
    endif()

    set(DRV_SRC_DIR ${DRV_DIR}/Src)
    set(DRV_INC_DIR ${DRV_DIR}/Inc)
    set(CMSIS_INC_DIR ${CMSIS_DIR}/Include)
    set(CMSIS_DEV_INC_DIR ${CMSIS_DIR}/Device/ST/STM32F1xx/Include)
else()
    message(FATAL_ERROR "Unsupported vendor: ${VENDOR}.")
endif()

file(GLOB DRV_SRC_ALL
    "${DRV_SRC_DIR}/*.c"
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${DRV_SRC_ALL})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMSIS_INC_DIR}
    ${CMSIS_DEV_INC_DIR}
    ${DRV_INC_DIR}
)
