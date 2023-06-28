#include "main.h"

/**
 * printOut_char - Prints a character
 * @types: this is a list of arguments
 * @buffer: temporal memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: precision modification
 * @size: Size specifier
 * Return: a printed character
 */

int printOut_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handleWriteChar(c, buffer, flags, width, precision, size));
}

/**
 * printOutString - Prints a string
 * @types: contains list of arguments
 * @buffer: temporal memory to handle print
 * @flags:  Computed active flags
 * @width: width of the string.
 * @precision: Precision specificier
 * @size: Size specifier
 * Return: a series of printed characters
 */
int printOutString(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, y;
	char *str = va_arg(types, char *);

	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & FLAG_MINUS)
		{
			write(1, &str[0], len);
			for (y = width - len; y > 0; y--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (y = width - len; y > 0; y--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}

/**
 * printOutPercent - Prints percentage/modulus(%) sign
 * @types: contains lists of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specificier
 * @size: Size specifier
 * Return: character '%'
 */
int printOutPercent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	NOT_USED(types);
	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);
	return (write(1, "%%", 1));
}


/**
 * printOutInteger - Print integer(s)
 * @types: contains a list of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s)
 */
int printOutInteger(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int y = BUFFER_SIZE - 2;
	int isNegative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convertSizeNumber(n, size);

	if (n == 0)
		buffer[y--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		isNegative = 1;
	}

	while (num > 0)
	{
		buffer[y--] = (num % 10) + '0';
		num /= 10;
	}

	y++;

	return (writeNumber(isNegative, y, buffer, flags, width, precision, size));
}


/**
 * printOut_bin - Prints an unsigned number
 * @types: contains lists of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: printed character(s)
 */
int printOut_bin(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, y, sum;
	unsigned int a[32];
	int count;

	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (y = 1; y < 32; y++)
	{
		m /= 2;
		a[y] = (n / m) % 2;
	}
	for (y = 0, sum = 0, count = 0; y < 32; y++)
	{
		sum += a[y];
		if (sum || y == 31)
		{
			char z = '0' + a[y];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
