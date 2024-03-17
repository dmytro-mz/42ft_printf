/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_single_format.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:28:17 by dmoroz            #+#    #+#             */
/*   Updated: 2024/03/16 18:01:07 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_SINGLE_FORMAT_H
# define PRINT_SINGLE_FORMAT_H

# include "../libft/libft.h"
# include <stdarg.h>

typedef struct s_foramt_config
{
	int			alt_form;
	int			zero_padding;
	int			left_adjusted;
	int			space_before_pos;
	int			force_sign;
	int			min_width;
	int			precision;
	char		conversion;
}				t_foramt_config;

t_foramt_config	parse_format_config(const char *format);
int				print_int_conv(t_foramt_config conf, va_list args);
int				print_uint_conv(t_foramt_config conf, va_list args);
// int				print_lhex_conv(t_foramt_config conf, va_list args);
// int				print_uhex_conv(t_foramt_config conf, va_list args);
int				print_char_conv(t_foramt_config conf, va_list args);
int				print_str_conv(t_foramt_config conf, va_list args);
// int				print_ptr_conv(t_foramt_config conf, va_list args);
int				print_pct_conv(t_foramt_config conf, va_list args);
const char		*skip_digits(const char *str);
int				do_on_space_pading(t_foramt_config conf, char *str, int len);

#endif