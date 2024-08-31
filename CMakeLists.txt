cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)

project(temp_nucleo C CXX ASM)

pico_sdk_init()

add_executable(temp_nucleo
        main.c
        )

target_link_libraries(temp_nucleo pico_stdlib pico_cyw43_arch_none hardware_adc)

#configura a saída padrão como sendo uma 'Serial-Over USB'
pico_enable_stdio_usb(temp_nucleo 1)
pico_enable_stdio_uart(temp_nucleo 0)


# create map/bin/hex file etc.
pico_add_extra_outputs(temp_nucleo)