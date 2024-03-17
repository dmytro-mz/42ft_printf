/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:40:15 by dmoroz            #+#    #+#             */
/*   Updated: 2024/03/17 18:31:59 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_single_format.h"

int	print_char_conv(t_foramt_config conf, va_list args)
{
	char	c[2];

	c[1] = 0;
	c[0] = va_arg(args, int);
	if (conf.min_width > 1)
		return (do_on_space_pading(conf, ft_strdup(c), 1));
	ft_putchar_fd(c[0], 1);
	return (1);
}
