#include "../include/print/uart.h"

//ref  <https://www.bilibili.com/video/BV1Q5411w7z5>

void Init_uart()								//Initial  ther uart
{
	printf("Initial uart...\n");
	/* disable interrupts. */
	uart_write_reg(IER, 0x00);

	uint8_t lcr = uart_read_reg(LCR);
	uart_write_reg(LCR, lcr | (1 << 7));
	uart_write_reg(DLL, 0x03);		//set the baud
	uart_write_reg(DLM, 0x00);

	lcr = 0;
	uart_write_reg(LCR, lcr | (3 << 0));
	
	uint8_t ier = uart_read_reg(IER);
	uart_write_reg(IER, ier | (1 << 0));

}

int uart_putc(char ch)						//put a char on screen by uart0
{
	while ((uart_read_reg(LSR) & LSR_TX) == 0);
	return uart_write_reg(THR, ch);
}

void uart_puts(char *s)						//put a string on screen by uart0
{
	while (*s) {
		uart_putc(*s++);
	}
}

int uart_getc()										//get a char from keyboard by uart0
{
	if(uart_read_reg(LSR) & LSR_RX)
	{
		return uart_read_reg(RHR);
	}
	else return -1;
}

void uart_console()								//to show char on the console
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
		}
	}
}

