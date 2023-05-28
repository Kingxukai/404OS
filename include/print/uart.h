#ifndef _UART_H__
#define _UART_H__

#include "../type.h"
#include "../platform.h"

//refer to  <https://www.bilibili.com/video/BV1Q5411w7z5>

#define UART_REG(reg) ((volatile uint8_t *)(UART0 + reg))

#define RHR 0	// Receive Holding Register (read mode)
#define THR 0	// Transmit Holding Register (write mode)
#define DLL 0	// LSB of Divisor Latch (write mode)
#define IER 1	// Interrupt Enable Register (write mode)
#define DLM 1	// MSB of Divisor Latch (write mode)
#define FCR 2	// FIFO Control Register (write mode)
#define ISR 2	// Interrupt Status Register (read mode)
#define LCR 3	// Line Control Register
#define MCR 4	// Modem Control Register
#define LSR 5	// Line Status Register
#define MSR 6	// Modem Status Register
#define SPR 7	// ScratchPad Register

#define LSR_RX (1 << 0)
#define LSR_TX (1 << 5)

#define uart_read_reg(reg) (*(UART_REG(reg)))
#define uart_write_reg(reg, v) (*(UART_REG(reg)) = (v))

void Init_uart();
int uart_putc(char ch);
void uart_puts(char *s);
int uart_getc();
void uart_console();

#endif
