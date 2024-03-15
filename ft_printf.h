#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>

int     ft_printf(const char *format, ...);
const   char *skip_single_format(const char *str);
int     print_single_format(const char *format, va_list args);

#endif
