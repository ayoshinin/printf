#include "main.h"

/**
 * getSize - computes the size to cast the argument
 * @format: formated str that contains all arguments to be printed
 * @y: list of arguments to be printed.
 *
 * Return: size
 */

int getSize(const char *format, int *y)
{
	int current_y = *y + 1;
	int size = 0;

	if (format[current_y] == 'l')
		size = SIZE_LONG;
	else if (format[current_y] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*y = current_y - 1;
	else
		*y = current_y;

	return (size);
}
