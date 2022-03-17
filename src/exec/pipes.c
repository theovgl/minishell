/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:14:53 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/17 18:43:39 by abiju-du         ###   ########.fr       */
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
		exit(g_return);
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
		g_return = WEXITSTATUS(status);
		return (g_return);
	}
	while (ret_wait != -1)
		ret_wait = wait(NULL);
	return (SUCCESS);
}

int	exec_pipes(t_config *c, char *envp[])
{
	t_list	*current;
	t_io	io;
	int		last_pid;

	io.in = 0;
	io.out = 1;
	current = c->cmd_list;
	while (current)
	{
		last_pid = fork();
		g_child = 1;
		if (last_pid < 0)
			exit_failure(c, "", 1);
		if (last_pid == 0)
			childhood(c, ((t_cmd *)(current->content)), envp);
		current = current->next;
	}
	closer(c, io);
	return (wait_for_children(last_pid));
}
