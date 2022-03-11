/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:12:51 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/10 16:12:53 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_config *c, t_cmd *cmd)
{
	int	exit_status;

	if (cmd->cmd[1])
		exit_status = ft_atoi(cmd->cmd[1]);
	else
		exit_status = -1;
	clean_on_success(c);
	printf("exit\n");
	ft_lstclear(&c->env, free);
	if (exit_status != -1)
		exit(exit_status);
	exit(0);
}
