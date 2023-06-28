#include "main.h"

/**
 * getPrecision - computes the precision to be printed out.
 * @format: formatted string in which to print the arguments.
 * @y: list of arguments to be printed out.
 * @arg_list: list of arguments.
 * Return: Precision.
 */

int getPrecision(const char *format, int *y, va_list arg_list)
{
	int current_y = *y + 1;
	int precision = -1;

	if (format[current_y] != '.')
		return (precision);

	precision = 0;

	for (current_y += 1; format[current_y] != '\0'; current_y++)
	{
		if (isDigit(format[current_y]))
		{
			precision *= 10;
			precision += format[current_y] - '0';
		}
		else if (format[current_y] == '*')
		{
			current_y++;
			precision = va_arg(arg_list, int);
			break;
		}
		else
			break;
	}

	*y = current_y - 1;

	return (precision);
}
