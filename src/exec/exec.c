/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:26:44 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/28 16:53:19 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief First version of exec that only accepts one non builtin executable 
 * and execute it in a parallel process
 * 
 * @param c 
 * @return int 
 */
int	exec(t_config *c, char *envp[])
{
	int		pid;
	int		fd_tmp;
	t_cmd	*cmd;

	cmd = (t_cmd *)(c->cmd_list->content);
	c->cmd_list->type = NOT_BUILTIN;
	if (c->cmd_list->type == NOT_BUILTIN)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(cmd->path, cmd->cmd, envp);
			perror("");
			return (SUCCESS);
		}
		wait(NULL);
	}
	else
		return (FAILURE);
}
