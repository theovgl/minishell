/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:26:44 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/07 17:02:21 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_config *c, t_cmd *cmd)
{
	if (ft_strncmp("echo", cmd->cmd[0], 4) == 0)
		echo(cmd->cmd);
	else if (ft_strncmp("cd", cmd->cmd[0], 2) == 0)
		cd(cmd->cmd[1]);
	else if (ft_strncmp("pwd", cmd->cmd[0], 3) == 0)
		pwd();
	else if (ft_strncmp("export", cmd->cmd[0], 6) == 0)
		export(c, cmd->cmd[1]);
	else if (ft_strncmp("unset", cmd->cmd[0], 5) == 0)
		unset(c, cmd->cmd);
	else if (ft_strncmp("env", cmd->cmd[0], 3) == 0)
		print_env(c);
}

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
	t_cmd	*cmd;

	cmd = (t_cmd *)(c->cmd_list->content);
	if (cmd->cmd == NULL)
		return (SUCCESS);
	if (!cmd->builtin)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(cmd->io.in, STDIN_FILENO);
			dup2(cmd->io.out, STDOUT_FILENO);
			execve(cmd->path, cmd->cmd, envp);
			perror(cmd->cmd[0]);
			exit(pid);
			return (SUCCESS);
		}
		wait(NULL);
	}
	else if (cmd->builtin)
	{
		exec_builtin(c, cmd);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
