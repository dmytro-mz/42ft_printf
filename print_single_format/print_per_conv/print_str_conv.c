/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:40:15 by dmoroz            #+#    #+#             */
/*   Updated: 2024/03/16 18:09:33 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../print_single_format.h"

int	print_str_conv(t_foramt_config conf, va_list args)
{
	char	*s;
	int		len;

	s = va_arg(args, char *);
	len = ft_strlen(s);
	if (conf.precision >= 0 && conf.precision < len)
	{
		s[conf.precision] = 0;
		len = conf.precision;
	}
	if (conf.min_width > len)
		return (do_on_space_pading(conf, s, len));
	ft_putstr_fd(s, 1);
	return (len);
}
