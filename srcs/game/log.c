#include <stdio.h>
#include <stdarg.h>

FILE *f;

void	init_log(const char *logfile)
{
	f = fopen(logfile, "w");
	setvbuf(f, NULL, _IONBF, 0);
}

void	do_log(const char *str, ...)
{
	va_list	ap;

	va_start(ap, str);
	vfprintf(f, str, ap);
}
