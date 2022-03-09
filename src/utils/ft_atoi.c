/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:34:05 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/09 15:24:33 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	calc;
	int	result;

	i = 0;
	result = 0;
	calc = 1;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	while (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i] == 45)
			calc = calc * -1;
		if (nptr[i + 1] == 45 || nptr[i + 1] == 43)
			return (0);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	result = result * calc;
	return (result);
}
