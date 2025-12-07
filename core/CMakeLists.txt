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
        set(CORE_DIR "stm32/f1xx")
    else()
        message(FATAL_ERROR "Unsupported STM32 series: ${SERIES}.")
    endif()

    set(CORE_SRC_DIR "${CORE_DIR}/src")
    set(CORE_INC_DIR "${CORE_DIR}/inc")
else()
    message(FATAL_ERROR "Unsupported vendor: ${VENDOR}.")
endif()

file(GLOB DRV_SRC_ALL
    "${CORE_SRC_DIR}/*.c"
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${DRV_SRC_ALL})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CORE_INC_DIR}
)
