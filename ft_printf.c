#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
	va_list args;
	int total;
	const char *tmp;
	
	total = 0;
	va_start(args, format);
	while (*format)
	{
	    tmp = ft_strchr(format, '%');
	    if (tmp)
	    {
	        total += tmp - format;
	        write(1, format, tmp - format);
	        total += print_single_format(tmp, args);
	        format = skip_single_format(tmp);
	    }
	    else
	    {
	        total += ft_strlen(format);
	        write(1, format, tmp - format);
	        format = tmp;
	    }
	}
	va_end(args);
	return (total);
}
