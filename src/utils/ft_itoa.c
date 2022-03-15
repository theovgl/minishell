/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 08:25:35 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/15 15:41:42 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	int_len(unsigned int nb)
{
	int	div;
	int	len;

	len = 0;
	div = nb;
	while (div != 0)
	{
		div /= 10;
		len++;
	}
	return (len);
}

int	ft_nb(int n)
{
	int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	return (nb);
}

int	ft_neg(int n)
{
	int	neg;

	if (n < 0)
		neg = 1;
	else
		neg = 0;
	return (neg);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				neg;
	unsigned int	nb;

	nb = ft_nb(n);
	neg = ft_neg(n);
	if (n == 0)
		i = 1;
	else
		i = neg + int_len(nb);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i] = 0;
	if (n == 0)
		str[0] = '0';
	while (nb != 0)
	{
		str[--i] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (neg != 0)
		str[0] = '-';
	return (str);
}
