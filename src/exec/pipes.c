/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:14:53 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/18 17:22:17 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	closer(t_config *c, t_io io)
{
	t_list	*current;

	current = c->cmd_list;
	while (current)
	{
		if (((t_cmd *)(current->content))->io.in != io.in
		&& ((t_cmd *)(current->content))->io.in != STDIN_FILENO)
		{
			close(((t_cmd *)(current->content))->io.in);
		}
		if (((t_cmd *)(current->content))->io.out != io.out
		&& ((t_cmd *)(current->content))->io.out != STDOUT_FILENO)
		{
			close(((t_cmd *)(current->content))->io.out);
		}
		current = current->next;
	}
}

static void	childhood(t_config *c, t_cmd *content, char **envp)
{
	closer(c, content->io);
	if (content->io.in != STDIN_FILENO)
	{
		dup2(content->io.in, STDIN_FILENO);
		close(content->io.in);
	}
	if (content->io.out != STDOUT_FILENO)
	{
		dup2(content->io.out, STDOUT_FILENO);
		close(content->io.out);
	}
	if (content->builtin)
	{
		exec_builtin(c, content);
		exit(g_global.ret);
	}
	else
	{
		execve(content->path, content->cmd, envp);
		check_cmd_not_found(c, content->path);
		check_permission_denied(c, content);
		close(content->io.in);
		close(content->io.out);
		exit_failure(c, content->cmd[0], 1);
	}
}

static int	wait_for_children(int last_pid)
{
	int	status;
	int	ret_wait;

	ret_wait = 0;
	waitpid(last_pid, &status, 1);
	if (WIFEXITED(status))
	{
		g_global.ret = WEXITSTATUS(status);
		return (g_global.ret);
	}
	while (ret_wait != -1)
		ret_wait = wait(NULL);
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}

int	exec_pipes(t_config *c, char *envp[])
{
	t_list	*current;
	t_io	io;

	io.in = 0;
	io.out = 1;
	current = c->cmd_list;
	while (current)
	{
		g_global.pid = fork();
		g_global.child = 1;
		if (g_global.pid < 0)
			exit_failure(c, "", 1);
		signal(SIGQUIT, handle_sigquit);
		if (g_global.pid == 0)
			childhood(c, ((t_cmd *)(current->content)), envp);
		current = current->next;
	}
	closer(c, io);
	return (wait_for_children(g_global.pid));
}
