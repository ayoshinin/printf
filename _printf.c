#include "main.h"

void printAllBuffer(char buffer[], int *buffer_index);

/**
 * _printf - Prints string output to stdout,
 * from the passed in argurments on the right.
 * @format: user input characters to be printed
 * Return: a string(array of characters)
 */

int _printf(const char *format, ...)
{
	int y, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list arg_list;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);

	for (y = 0; format && format[y] != '\0'; y++)
	{
		if (format[y] != '%')
		{
			buffer[buffer_index++] = format[y];
			if (buffer_index == BUFFER_SIZE)
				printAllBuffer(buffer, &buffer_index);
			printed_chars++;
		}
		else
		{
			printAllBuffer(buffer, &buffer_index);
			flags = getFlags(format, &y);
			width = getWidth(format, &y, arg_list);
			precision = getPrecision(format, &y, arg_list);
			size = getSize(format, &y);
			++y;
			printed = handlePrintOut(format, &y, arg_list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	printAllBuffer(buffer, &buffer_index);

	va_end(arg_list);

	return (printed_chars);
}

/**
 * printAllBuffer - Prints the contents of
 * the buffer if any exist
 * @buffer: temporary memory to hold array of character
 * @buffer_index: Index at which to hold next character,
 * and may also represent the len.
 */

void printAllBuffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}
