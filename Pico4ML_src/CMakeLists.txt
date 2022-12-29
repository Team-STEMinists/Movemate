
cmake_minimum_required(VERSION 3.12)

project(imu_read C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)


add_executable(imu_read)
pico_generate_pio_header(imu_read ${CMAKE_CURRENT_LIST_DIR}/uart_tx.pio)
pico_generate_pio_header(imu_read ${CMAKE_CURRENT_LIST_DIR}/uart_rx.pio)

target_sources(imu_read PRIVATE read.cpp ICM42622.cpp UART_TxRx.cpp fonts.c) # CMAKE -> C (compiler)
target_link_libraries(imu_read PRIVATE pico_stdlib hardware_pio hardware_i2c hardware_pwm LCD_st7735) # CMAKE -> C (linker)
#target_link_libraries(imu_read PUBLIC hardware_i2c pico_stdlib)
pico_enable_stdio_usb(imu_read 1) # PICO SDK (USB)
pico_enable_stdio_uart(imu_read 0) # PICO SDK (USB)

pico_add_extra_outputs(imu_read)

