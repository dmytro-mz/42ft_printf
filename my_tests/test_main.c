/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoroz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:14:52 by dmoroz            #+#    #+#             */
/*   Updated: 2024/03/20 19:55:07 by dmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	run_tests(int (*f)());

int	main(int ac, char *av[])
{
	void	*func;

	if (ac == 2)
	{
		if (!strcmp(av[1], "printf"))
			func = &printf;
		else if (!strcmp(av[1], "ft_printf"))
			func = &ft_printf;
		else
		{
			printf("ERROR: Wrong function name \"%s\".", av[1]);
			return (0);
		}
		run_tests(func);
	}
	else
		printf("ERROR: Provide function name.");
	return (0);
}
