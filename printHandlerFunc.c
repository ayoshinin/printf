#include "main.h"
/**
 * handlePrintOut - prints argument according to the type
 * @fmtg: formated str that contains all arguments to be printed
 * @arg_list: list of arguments to be printed.
 * @index: ind.
 * @buffer: temp memory to handle print.
 * @flags: computed active flags
 * @width: width of the string.
 * @precision: Precision specified
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handlePrintOut(const char *fmtg, int *index, va_list arg_list,
		char buffer[], int flags, int width, int precision, int size)
{
	int y, undetermined_len = 0, printed_chars = -1;
	fmtg_t fmtg_types[] = {
		{'c', printOut_char}, {'s', printOutString}, {'%', printOutPercent},
		{'i', printOutInteger}, {'d', printOutInteger}, {'b', printOut_bin},
		{'u', printOutUnsigned}, {'o', printOut_octal}, {'x', printOutHex},
		{'X', printOutHexUppercase}, {'p', printOutAddress},
		{'S', printOutNonPrintable},
		{'r', PrintOutReverse}, {'R', PrintOutRot13String},
		{'\0', NULL}
	};
	for (y = 0; fmtg_types[y].fmtg != '\0'; y++)
		if (fmtg[*index] == fmtg_types[y].fmtg)
			return (fmtg_types[y].func_ptr(arg_list, buffer,
						flags, width, precision, size));

	if (fmtg_types[y].fmtg == '\0')
	{
		if (fmtg[*index] == '\0')
			return (-1);
		undetermined_len += write(1, "%%", 1);
		if (fmtg[*index - 1] == ' ')
			undetermined_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmtg[*index] != ' ' && fmtg[*index] != '%')
				--(*index);
			if (fmtg[*index] == ' ')
				--(*index);
			return (1);
		}
		undetermined_len += write(1, &fmtg[*index], 1);
		return (undetermined_len);
	}
	return (printed_chars);
}
