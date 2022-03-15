/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:14:53 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/15 22:38:31 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closer(t_config *c, t_io io)
{
	t_list	*current;
// printf("io.in == %d\nio.out == %d\n", io.in, io.out);

	current = c->cmd_list;
	while (current)
	{
		if (((t_cmd *)(current->content))->io.in != io.in && ((t_cmd *)(current->content))->io.in != STDIN_FILENO)
		{
			close(((t_cmd *)(current->content))->io.in);
// printf("closed io.in == %d\n", ((t_cmd *)(current->content))->io.in);
		}
		if (((t_cmd *)(current->content))->io.out != io.out && ((t_cmd *)(current->content))->io.in != STDOUT_FILENO)
		{
			close(((t_cmd *)(current->content))->io.out);
// printf("closed io.out == %d\n", ((t_cmd *)(current->content))->io.out);
		}
		current = current->next;
	}
}

int	exec(t_config *c, char *envp[])
{

	t_list	*current;
	t_list	*tmp;
	int		last_pid;
	int		i;
	int		status;

	i = 1;
	current = c->cmd_list;
	if (current->next || !((t_cmd *)(current->content))->builtin)
	{
		i = 0;
		while (current)
		{
			last_pid = fork();
			if (last_pid < 0)
				exit_failure(c, "", 1);
			if (last_pid == 0)
			{
				
				if (((t_cmd *)(current->content))->builtin)
				{
					exec_builtin(c, ((t_cmd *)(current->content)));
					return (SUCCESS);
				}
				closer(c, ((t_cmd *)(current->content))->io);
				dup2(((t_cmd *)(current->content))->io.in, STDIN_FILENO);
				dup2(((t_cmd *)(current->content))->io.out, STDOUT_FILENO);
				execve(((t_cmd *)(current->content))->path, ((t_cmd *)(current->content))->cmd, envp);
				check_cmd_not_found(c, ((t_cmd *)(current->content))->path);
				check_permission_denied(c, ((t_cmd *)(current->content)));
				close(((t_cmd *)(current->content))->io.in);
				close(((t_cmd *)(current->content))->io.out);
				exit_failure(c, ((t_cmd *)(current->content))->cmd[0], 1);
			}
			tmp = current;
			current = current->next;
			if (!i)
				close(((t_cmd *)(current->content))->io.in);
			i++;
		}
		waitpid(last_pid, &status, 1);
		if (WIFEXITED(status))
		{
			g_return = WEXITSTATUS(status);
			return (g_return);
		}
		while (--i)
			wait(NULL);
		close(((t_cmd *)(tmp->content))->io.out);
	}
	else if (((t_cmd *)(current->content))->builtin)
	{
		exec_builtin(c, ((t_cmd *)(current->content)));
		return (SUCCESS);
	}
	else
		return (FAILURE);
}