/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvariable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:33:02 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/15 15:01:20 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvariable(char *var)
{
	int	i;

	i = 0;
	if (var[i] != '_' && !ft_isalpha(var[i]))
	{
		return (0);
	}
	while (var[i])
	{
		if (var[i] != '_' && var[i] != '-' && !ft_isalnum(var[i]))
			return (0);
		i++;
	}
	return (1);
}
