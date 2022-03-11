/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:03:02 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/11 14:46:07 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_config *c, t_cmd *cmd)
{
	int	exit_status;

	if (cmd->cmd[1])
		exit_status = ft_atoi(cmd->cmd[1]);
	else
		exit_status = g_return;
	clean(c);
	printf("exit\n");
	ft_lstclear(&c->env, free);
	if (exit_status != 0)
		exit(exit_status);
	exit(0);
}
