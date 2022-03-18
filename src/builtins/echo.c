/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:55:22 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/18 12:43:15 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *av[], int *pos)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	if (av[1] && av[1][0] == '-' && av[1][1] == 'n')
	{
		nl = 1;
		*pos += 1;
	}
	else
		nl = 0;
	return (nl);
}

/**
 * @brief Act like echo on shell but only accepts the option: '-n'
 *
 * @param av
 * @return int
 */
int	echo(t_cmd *cmd)
{
	int		i;
	int		nl;
	char	**av;

	i = 1;
	av = cmd->cmd;
	nl = check_option(av, &i);
	while (av[i])
	{
		ft_putstr_fd(av[i], cmd->io.out);
		i++;
		if (av[i])
			ft_putchar_fd(' ', cmd->io.out);
	}
	if (nl == 0)
		ft_putchar_fd('\n', cmd->io.out);
	g_return = 0;
	return (SUCCESS);
}
