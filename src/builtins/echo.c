/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:55:22 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/04 18:31:33 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *av[], int *pos)
{
	int	i;
	int	j;
	int	nl;

	i = 1;
	nl = 0;
	while (av[i])
	{
		j = 1;
		if (av[i][0] == '-')
		{
			*pos += 1;
			while (av[i][j])
			{
				if (av[i][j] != 'n')
					nl = 0;
				else
					nl = 1;
				j++;
			}
		}
		i++;
	}
	return (nl);
}

/**
 * @brief Act like echo on shell but only accepts the option: '-n'
 *
 * @param av
 * @return int
 */
int	echo(char *av[])
{
	int	i;
	int	nl;

	i = 1;
	nl = check_option(av, &i);
	while (av[i])
	{
		printf("%s", av[i]);
		i++;
		if (av[i])
			printf(" ");
	}
	if (nl == 0)
		printf("\n");
	return (SUCCESS);
}
