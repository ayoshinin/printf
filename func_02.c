#include "main.h"


/**
 * printOutAddress - Prints the value contained by pointer variable
 * @types: contains a list of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s).
 */
int printOutAddress(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extraChar = 0, padding = ' ';
	int index = BUFFER_SIZE - 2, len = 2, padding_start = 1;
	unsigned long num_address;
	char mapTo[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	NOT_USED(width);
	NOT_USED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	NOT_USED(precision);

	num_address = (unsigned long)addrs;

	while (num_address > 0)
	{
		buffer[index--] = mapTo[num_address % 16];
		num_address /= 16;
		len++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';
	if (flags & FLAG_PLUS)
		extraChar = '+', len++;
	else if (flags & FLAG_SPACE)
		extraChar = ' ', len++;

	index++;

	return (writeAddress(buffer, index, len,
		width, flags, padding, extraChar, padding_start));
}

/**
 * printOutNonPrintable - Prints ascii codes,
 * in hexadecimal notation, of non printable chars
 * @types: contains a list of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s)
 */
int printOutNonPrintable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int y = 0, offset = 0;
	char *str = va_arg(types, char *);

	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[y] != '\0')
	{
		if (isPrintable(str[y]))
			buffer[y + offset] = str[y];
		else
			offset += appendHexaCode(str[y], buffer, y + offset);

		y++;
	}

	buffer[y + offset] = '\0';

	return (write(1, buffer, y + offset));
}


/**
 * PrintOutReverse - Prints strings in reverse order.
 * @types: contains a list of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: printed character(s)
 */

int PrintOutReverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int y, count = 0;

	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		NOT_USED(precision);

		str = ")Null(";
	}
	for (y = 0; str[y]; y++)
		;

	for (y = y - 1; y >= 0; y--)
	{
		char z = str[y];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * PrintOutRot13String - Prints a rot13 string.
 * @types: contains a list of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: printed character(s)
 */
int PrintOutRot13String(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int y, m;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (y = 0; str[y]; y++)
	{
		for (m = 0; in[m]; m++)
		{
			if (in[m] == str[y])
			{
				x = out[m];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[m])
		{
			x = str[y];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
