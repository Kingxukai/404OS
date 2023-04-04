void uart_init()
{
	//close interruption
}

void uart_putc(char c)
{
	
}

void uart_puts(char *s)
{
	while(*s != '\0')
	{
		uart_putc(*s++);
	}
}
