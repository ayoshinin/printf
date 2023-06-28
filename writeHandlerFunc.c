#include "main.h"

/**
 * handleWriteChar - Prints a string
 * @c: char types.
 * @buffer: temp memory to handle print
 * @flags:  computed active flags.
 * @width: width of the string.
 * @precision: precision specifier
 * @size: Size specifier
 * Return: Printed character(s).
 */

int handleWriteChar(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int y = 0;
	char padding = ' ';

	NOT_USED(precision);
	NOT_USED(size);

	if (flags & FLAG_ZERO)
		padding = '0';

	buffer[y++] = c;
	buffer[y] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (y = 0; y < width - 1; y++)
			buffer[BUFFER_SIZE - y - 2] = padding;

		if (flags & FLAG_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - y - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - y - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * writeNumber - Prints a string
 * @isNegative: list of arguments
 * @index: char types.
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Printed character(s).
 */

int writeNumber(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFFER_SIZE - index - 1;
	char padding = ' ', extraChar = 0;

	NOT_USED(size);

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';
	if (isNegative)
		extraChar = '-';
	else if (flags & FLAG_PLUS)
		extraChar = '+';
	else if (flags & FLAG_SPACE)
		extraChar = ' ';

	return (write_num(index, buffer, flags, width, precision,
		len, padding, extraChar));
}

/**
 * write_num - Write a number using a bufffer
 * @index: position at which the number starts on the buffer
 * @buffer: temporary memory to hold array of character
 * @flags: flag specified
 * @width: width of the string.
 * @prec: Precision specifier
 * @len: Number len character-wise
 * @padding: Padding character
 * @extraChar: Extra character
 *
 * Return: number of printed character(s).
 */

int write_num(int index, char buffer[], int flags, int width, int prec,
	int len, char padding, char extraChar)
{       int y, padding_start = 1;

	if (prec == 0 && index == BUFFER_SIZE - 2 &&
			buffer[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFFER_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padding = ' ';
	if (prec > 0 && prec < len)
		padding = ' ';
	while (prec > len)
		buffer[--index] = '0', len++;
	if (extraChar != 0)
		len++;
	if (width > len)
	{
		for (y = 1; y < width - len + 1; y++)
			buffer[y] = padding;
		buffer[y] = '\0';
		if (flags & FLAG_MINUS && padding == ' ')
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], len) + write(1, &buffer[1], y - 1));
		}
		else if (!(flags & FLAG_MINUS) && padding == ' ')
		{
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[1], y - 1) + write(1, &buffer[index], len));
		}
		else if (!(flags & FLAG_MINUS) && padding == '0')
		{
			if (extraChar)
				buffer[--padding_start] = extraChar;
			return (write(1, &buffer[padding_start], y - padding_start) +
				write(1, &buffer[index], len - (1 - padding_start)));
		}
	}
	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], len));
}

/**
 * writeUnsignd - Writes an unsigned number
 * @isNegative: indicate if the number is negative
 * @index: position at which the number starts on the buffer
 * @buffer: temporary memory to hold array of character
 * @flags: flag specified
 * @width: width of the string.
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: number of written character(s)
 */

int writeUnsignd(int isNegative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFFER_SIZE - index - 1, y = 0;
	char padding = ' ';

	NOT_USED(isNegative);
	NOT_USED(size);

	if (precision == 0 && index == BUFFER_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < len)
		padding = ' ';

	while (precision > len)
	{
		buffer[--index] = '0';
		len++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';

	if (width > len)
	{
		for (y = 0; y < width - len; y++)
			buffer[y] = padding;

		buffer[y] = '\0';

		if (flags & FLAG_MINUS)
		{
			return (write(1, &buffer[index], len) + write(1, &buffer[0], y));
		}
		else
		{
			return (write(1, &buffer[0], y) + write(1, &buffer[index], len));
		}
	}

	return (write(1, &buffer[index], len));
}

/**
 * writeAddress - Writes the memory address
 * @buffer: temporary memory to hold array of character
 * @index: position at which, the number starts on the buffer
 * @len: Length of number character(s)
 * @width: width of the string.
 * @flags: flag specified.
 * @padding: character representing the padding
 * @extraChar: Character representing extra character
 * @padding_start: position at which padding starts
 *
 * Return: number of written characters.
 */

int writeAddress(char buffer[], int index, int len,
	int width, int flags, char padding, char extraChar, int padding_start)
{
	int y;

	if (width > len)
	{
		for (y = 3; y < width - len + 3; y++)
			buffer[y] = padding;
		buffer[y] = '\0';
		if (flags & FLAG_MINUS && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[index], len) + write(1, &buffer[3], y - 3));
		}
		else if (!(flags & FLAG_MINUS) && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extraChar)
				buffer[--index] = extraChar;
			return (write(1, &buffer[3], y - 3) + write(1, &buffer[index], len));
		}
		else if (!(flags & FLAG_MINUS) && padding == '0')
		{
			if (extraChar)
				buffer[--padding_start] = extraChar;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_start], y - padding_start) +
				write(1, &buffer[index], len - (1 - padding_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extraChar)
		buffer[--index] = extraChar;
	return (write(1, &buffer[index], BUFFER_SIZE - index - 1));
}
