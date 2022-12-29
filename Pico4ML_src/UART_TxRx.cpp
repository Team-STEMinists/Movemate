#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "uart_tx.pio.h"
#include <stdio.h>
#include "uart_rx.pio.h"
#include "UART_TxRx.h"

uint PIN_TX,SERIAL_BAUD,PIO_RX_PIN;

void UART_TR::UART_init(uint txpin,uint rxpin,uint baud){
    SERIAL_BAUD = baud;
    //Tx constants
    PIN_TX = txpin;
    //Rx constants
    PIO_RX_PIN = rxpin;

    uint offset1 = pio_add_program(pio0, &uart_tx_program);
    uart_tx_program_init(pio0, 0, offset1, PIN_TX, SERIAL_BAUD);

    uint offset2 = pio_add_program(pio1, &uart_rx_program);
    uart_rx_program_init(pio1, 0, offset2, PIO_RX_PIN, SERIAL_BAUD);
}

void UART_TR::U_tx(char c[]){
    uart_tx_program_puts(pio0, 0, c);
    sleep_ms(1);
    //printf("%s\n",c);
}

char UART_TR::U_rx(){
    char c;
    c = uart_rx_program_getc(pio1, 0);
    return c;
    //printf("%s\n",c);
}
