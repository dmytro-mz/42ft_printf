/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:36:46 by dmoroz            #+#    #+#             */
/*   Updated: 2024/03/17 11:22:06 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../print_single_format.h"

void	pad_zeros(t_foramt_config conf, char **num, int len, int is_neg);
void	add_sign(t_foramt_config conf, char **num, int is_neg);

int	print_int_conv(t_foramt_config conf, va_list args)
{
	char	*num;
	int		is_neg;
	int		len;

	num = ft_itoa(va_arg(args, int));
	if (!num)
		return (0);
	len = ft_strlen(num);
	is_neg = 0;
	if (num < 0)
	{
		is_neg = 1;
		ft_memmove(num, num + 1, len--);
	}
	pad_zeros(conf, &num, len, is_neg);
	add_sign(conf, &num, is_neg);
	len = ft_strlen(num);
	if (conf.min_width > len)
		return (do_on_space_pading(conf, num, len));
	ft_putstr_fd(num, 1);
	return (len);
}

void	pad_zeros(t_foramt_config conf, char **num, int len, int is_neg)
{
	int		expected_len;
	char	*tmp1;
	char	*tmp2;

	expected_len = 0;
	if (conf.precision >= 0)
		expected_len = conf.precision;
	else if (conf.zero_padding && conf.min_width > 0 && !conf.left_adjusted)
	{
		expected_len = conf.min_width - (conf.force_sign + conf.space_before_pos
				+ is_neg > 0);
	}
	if (expected_len > len)
	{
		tmp1 = (char *)malloc((expected_len - len + 1) * sizeof(char));
		ft_memset(tmp1, '0', expected_len - len);
		tmp1[expected_len - len] = 0;
		tmp2 = ft_strjoin(tmp1, *num);
		free(tmp1);
		free(*num);
		*num = tmp2;
	}
}

void	add_sign(t_foramt_config conf, char **num, int is_neg)
{
	char	*tmp;

	if (is_neg)
	{
		tmp = ft_strjoin("-", *num);
		free(*num);
		*num = tmp;
	}
	else if (conf.force_sign)
	{
		tmp = ft_strjoin("+", *num);
		free(*num);
		*num = tmp;
	}
	else if (conf.space_before_pos)
	{
		tmp = ft_strjoin(" ", *num);
		free(*num);
		*num = tmp;
	}
}
