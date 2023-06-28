#include "main.h"

/**
 * printOutUnsigned - Prints unsigned number
 * @types: contains lists of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s).
 */

int printOutUnsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int y = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convertSizeUnsignd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = (num % 10) + '0';
		num /= 10;
	}

	y++;

	return (writeUnsignd(0, y, buffer, flags, width, precision, size));
}

/**
 * printOut_octal - Prints octal notation of an unsigned number
 * @types: contains lists of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s)
 */

int printOut_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int y = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	NOT_USED(width);

	num = convertSizeUnsignd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & FLAG_HASH && init_num != 0)
		buffer[y--] = '0';

	y++;

	return (writeUnsignd(0, y, buffer, flags, width, precision, size));
}

/**
 * printOutHex - Prints hexadecimal notation of an unsigned number
 * @types: contains lists of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s)
 */

int printOutHex(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHexAll(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * printOutHexUppercase - Prints upper hexadecimal notation
 * of an unsigned number
 * @types: contains lists of arguments
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s)
 */

int printOutHexUppercase(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHexAll(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * printHexAll - Prints a hexadecimal number in lower- or upper-case
 * @types: contains lists of arguments
 * @mapTo: Array of values to map the number to
 * @buffer: temp memory to handle print
 * @flags:  computed active flags
 * @flag_ch: the flag char
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: Printed character(s)
 */

int printHexAll(va_list types, char mapTo[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int y = BUFFER_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	NOT_USED(width);

	num = convertSizeUnsignd(num, size);

	if (num == 0)
		buffer[y--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[y--] = mapTo[num % 16];
		num /= 16;
	}

	if (flags & FLAG_HASH && init_num != 0)
	{
		buffer[y--] = flag_ch;
		buffer[y--] = '0';
	}

	y++;

	return (writeUnsignd(0, y, buffer, flags, width, precision, size));
}
