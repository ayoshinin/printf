#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#define BUFFER_SIZE 1024
#define NOT_USED(x) (void)(x)

/* FLAG MACROS*/
#define FLAG_HASH 8
#define FLAG_SPACE 16
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4

/* SIZE MACROS */
#define SIZE_SHORT 1
#define SIZE_LONG 2

/**
 * struct fmtg - name of the struct
 *
 * @fmtg: format string
 * @func_ptr: blueprint of the associated functions
 */

struct fmtg
{
	char fmtg;
	int (*func_ptr)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmtg fmtg_t - short-form/alias for the struct
 *
 * @fmtg: format string
 * @fmg_t: shortened name for struct syntax
 */

typedef struct fmtg fmtg_t;

int _printf(const char *format, ...);
int handlePrintOut(const char *fmtg, int *y, va_list arg_list,
		char buffer[], int flags, int width, int precision, int size);

/* list of functions to print chars and strings */
int printOutString(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printOutPercent(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printOut_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* list of functions to print numbers */
int printOutInteger(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printOut_bin(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printOutHex(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printOutHexUppercase(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printOutUnsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int printOut_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int printHexAll(va_list types, char mapTo[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* this function prints non printable characters */
int printOutNonPrintable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* this function prints memory address */
int printOutAddress(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* these functions handle other specifiers */
int getFlags(const char *format, int *y);
int getSize(const char *format, int *y);
int getWidth(const char *format, int *y, va_list arg_list);
int getPrecision(const char *format, int *y, va_list arg_list);

/*this function prints string in reverse order*/
int PrintOutReverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*this function prints a string in rot 13*/
int PrintOutRot13String(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int writeAddress(char buffer[], int index, int len,
	int width, int flags, char padding, char extraChar, int padding_start);
int handleWriteChar(char c, char buffer[],
	int flags, int width, int precision, int size);
int writeNumber(int isPositive, int index, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int index, char b_ff[], int flags, int width, int precision,
	int len, char padding, char extraChar);
int writeUnsignd(int isNegative, int index,
char buffer[], int flags, int width, int precision, int size);

/*********** UTILS ****************/
long int convertSizeNumber(long int num, int size);
int isDigit(char);
int isPrintable(char);
int appendHexaCode(char, char[], int);
long int convertSizeUnsignd(unsigned long int num, int size);

#endif
