/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:26:44 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/15 15:41:13 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_config *c, t_cmd *cmd)
{
	int	size;

	size = ft_strlen(cmd->cmd[0]);
	if (ft_strncmp("echo", cmd->cmd[0], size) == 0)
		echo(cmd->cmd);
	else if (ft_strncmp("cd", cmd->cmd[0], size) == 0)
		cd(cmd->cmd[1]);
	else if (ft_strncmp("pwd", cmd->cmd[0], size) == 0)
		pwd();
	else if (ft_strncmp("export", cmd->cmd[0], size) == 0)
		ft_export(c, cmd->cmd);
	else if (ft_strncmp("unset", cmd->cmd[0], size) == 0)
		unset(c, cmd->cmd);
	else if (ft_strncmp("env", cmd->cmd[0], size) == 0)
		print_env(c, 0);
	else if (ft_strncmp("exit", cmd->cmd[0], size) == 0)
		ft_exit(c, cmd);
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
	t_cmd	*cmd;
	int		status;

	cmd = (t_cmd *)(c->cmd_list->content);
	if (cmd->cmd == NULL)
		return (SUCCESS);
	else if (!cmd->builtin)
	{
		g_pid = fork();
		g_child = 1;
		if (g_pid < 0)
			exit_failure(c, "Fork", 1);
		if (g_pid == 0)
		{
			dup2(cmd->io.in, STDIN_FILENO);
			dup2(cmd->io.out, STDOUT_FILENO);
			execve(cmd->path, cmd->cmd, envp);
			check_cmd_not_found(c, cmd->path);
			check_permission_denied(c, cmd);
			exit_failure(c, cmd->cmd[0], 1);
		}
		wait(&status);
		if (WIFEXITED(status))
		{
			g_return = WEXITSTATUS(status);
			return (g_return);
		}
	}
	else if (cmd->builtin)
	{
		exec_builtin(c, cmd);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
