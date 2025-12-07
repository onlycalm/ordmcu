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
        set(STRTUP_DIR "stm32/f103xe")
    else()
        message(FATAL_ERROR "Unsupported STM32 series: ${SERIES}.")
    endif()
else()
    message(FATAL_ERROR "Unsupported vendor: ${VENDOR}.")
endif()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${STRTUP_DIR}/strtup.s
)
