/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:24:00 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/18 17:13:21 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd_not_found(t_config *c, char *cmd_path)
{
	if (cmd_path == NULL)
	{
		g_global.ret = 127;
		exit_failure(c, "command not found\n", 0);
	}
	return ;
}

void	check_permission_denied(t_config *c, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "./", ft_strlen(cmd->cmd[0])) == 0)
	{
		g_global.ret = 126;
		exit_failure(c, cmd->cmd[0], 1);
	}
	if (access(cmd->cmd[0], R_OK | W_OK | X_OK) == -1)
	{
		g_global.ret = 126;
		exit_failure(c, cmd->cmd[0], 1);
	}
	return ;
}
