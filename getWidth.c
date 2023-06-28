#include "main.h"

/**
 * getWidth - computes the width of str to be printed
 * @format: formated str that contains all arguments to be printed
 * @y: list of arguments to be printed.
 * @arg_list: list of arguments.
 *
 * Return: width.
 */
int getWidth(const char *format, int *y, va_list arg_list)
{
	int current_y;
	int width = 0;

	for (current_y = *y + 1; format[current_y] != '\0'; current_y++)
	{
		if (isDigit(format[current_y]))
		{
			width *= 10;
			width += format[current_y] - '0';
		}
		else if (format[current_y] == '*')
		{
			current_y++;
			width = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}

	*y = current_y - 1;

	return (width);
}
