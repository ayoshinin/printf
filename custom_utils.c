#include "main.h"

/**
 * isPrintable - Assess for printable characters
 * @c: Character to be evaluated
 *
 * Return: 1 if c is printable, 0 not printable
 */

int isPrintable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * appendHexaCode - appends ascii to buffer,in hexadecimal code
 * @buffer: temporary memory to hold array of character
 * @y: Position from which to begin appending
 * @ascii_code: ASCII CODE.
 * Return: Always 3
 */

int appendHexaCode(char ascii_code, char buffer[], int y)
{
	char mapTo[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[y++] = '\\';
	buffer[y++] = 'x';

	buffer[y++] = mapTo[ascii_code / 16];
	buffer[y] = mapTo[ascii_code % 16];

	return (3);
}

/**
 * isDigit - assert if the provided char is a digit
 * @c: character to be evaluated
 *
 * Return: 1 if its a digit, 0 not a digit
 */

int isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convertSizeNumber - Casts a number according to the specified size
 * @num: number to be casted.
 * @size: indicates the type to be casted.
 *
 * Return: casted value of variable num
 */

long int convertSizeNumber(long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convertSizeUnsignd - Casts a number according to the specified size
 * @num: Number to be casted
 * @size: indicates the type to be casted
 *
 * Return: casted value of variable num
 */

long int convertSizeUnsignd(unsigned long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
