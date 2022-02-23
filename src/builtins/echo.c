/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:55:22 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/23 16:55:25 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Act like echo on shell but only accepts the option: '-n'
 * 
 * @param av 
 * @return int 
 */
int	echo(char *av[])
{
	int	i;

	i = 1;
	if (av[1][0] == '-' && av[1][1] == 'n' && av[1][2] == 0)
		i++;
	while (av[i])
	{
		printf("%s", av[i]);
		i++;
		if (av[i])
			write(1, " ", 1);
	}
	if (av[1][0] != '-' || av[1][1] != 'n' || av[1][2] != 0)
		printf("\n");
	return (SUCCESS);
}

// int main(int ac, char *av[])
// {
// 	if (ac < 2)
// 		return 1;
// 	echo(av);
// 	return 0;
// }
