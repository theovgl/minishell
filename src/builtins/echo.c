/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:55:22 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/18 23:02:04 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *av[], int *pos)
{
	int	nl;
	int	i;

	i = 1;
	nl = 0;
	while (av[*pos] && av[*pos][0] == '-')
	{
		i = 1;
		while (av[*pos][i] == 'n')
			i++;
		if (av[*pos][i] == 0)
		{
			nl = 1;
			*pos += 1;
		}
		else
			break ;
	}
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
	g_global.ret = 0;
	return (SUCCESS);
}
