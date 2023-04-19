#include "../include/uart.h"

void Init_uart()
{
	/* disable interrupts. */
	uart_write_reg(IER, 0x00);

	uint8_t lcr = uart_read_reg(LCR);
	uart_write_reg(LCR, lcr | (1 << 7));
	uart_write_reg(DLL, 0x03);
	uart_write_reg(DLM, 0x00);

	lcr = 0;
	uart_write_reg(LCR, lcr | (3 << 0));
	
	uint8_t ier = uart_read_reg(IER);
	uart_write_reg(IER, ier | (1 << 0));
}

int uart_putc(char ch)
{
	while ((uart_read_reg(LSR) & LSR_TX) == 0);
	return uart_write_reg(THR, ch);
}

void uart_puts(char *s)
{
	while (*s) {
		uart_putc(*s++);
	}
}

int uart_getc()
{
	if(uart_read_reg(LSR) & LSR_RX)
	{
		return uart_read_reg(RHR);
	}
	else return -1;
}

void uart_console()
{
	while(1)
	{
		int c = uart_getc();
		if(c == -1)
		{
			break;
		}
		else
		{
			uart_putc((char)c);
			uart_putc('\n');
		}
	}
}

