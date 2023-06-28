#include "main.h"

/**
 * getFlags - computed active flags
 * @format: formatted string in which to print the arguments
 * @y: a parameter is substituted here
 * Return: flag specified:
 */

int getFlags(const char *format, int *y)
{
	int m, current_y;
	int flags = 0;
	const char FLAG_CHARS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {FLAG_MINUS, FLAG_PLUS, FLAG_ZERO,
		FLAG_HASH, FLAG_SPACE, 0};

	for (current_y = *y + 1; format[current_y] != '\0'; current_y++)
	{
		for (m = 0; FLAG_CHARS[m] != '\0'; m++)
			if (format[current_y] == FLAG_CHARS[m])
			{
				flags |= FLAGS_ARRAY[m];
				break;
			}

		if (FLAG_CHARS[m] == 0)
			break;
	}

	*y = current_y - 1;

	return (flags);
}
