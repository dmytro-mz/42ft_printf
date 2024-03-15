#include "ft_printf.h"

const char *skip_flags(const char *str);
const char *skip_number(const char *str);
const char *skip_precision(const char *str);
const char *skip_conversion(const char *str);

const char *skip_single_format(const char *str)
{
    
    str++;
    str = skip_flags(str); // fix fact, that order of flags might be arbitral; use loop
    str = skip_number(str);
    str = skip_precision(str);
    str = skip_conversion(str);
    return (str);
}

const char *skip_flags(const char *str)
{
    if (*str == '#')
        str++;
    if (*str == '0')
        str++;
    if (*str == '-')
        str++;
    if (*str == ' ')
        str++;
    if (*str == '+')
        str++;
    return (str);
}

const char *skip_number(const char *str)
{
    while (ft_isdigit(*str))
        str++;
    return (str);
}

const char *skip_precision(const char *str)
{
    if (*str == '.')
        str++;
    return (skip_number(str));
}

const char *skip_conversion(const char *str)
{
    if (ft_strchr("cspdiuxX%", *str))
        str++;
    return (str);
}
