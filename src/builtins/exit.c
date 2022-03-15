/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:03:02 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/15 15:40:40 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static u_int8_t	check_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && cmd->cmd[1][1])
		i++;
	while (cmd->cmd[1][i])
	{
		if (!ft_isdigit(cmd->cmd[1][i]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			return (2);
		}
		i++;
	}
	i = 0;
	while (cmd->cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

void	ft_exit(t_config *c, t_cmd *cmd)
{
	u_int8_t	exit_status;

	printf("exit\n");
	exit_status = 0;
	if (cmd->cmd[1])
	{
		exit_status = check_args(cmd);
	}
	if (exit_status == 1)
	{
		g_return = 1;
		return ;
	}
	if (exit_status == 0)
	{
		if (cmd->cmd[1])
			exit_status = ft_atoi(cmd->cmd[1]);
		else
			exit_status = g_return;
	}
	clean(c);
	ft_lstclear(&c->env, free);
	if (exit_status != 0)
		exit(exit_status);
	exit(0);
}
