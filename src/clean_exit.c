/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:24:45 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/15 16:55:42 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd_list(t_list *cmd_list)
{
	t_list	*current;
	int		i;

	current = cmd_list;
	while (current)
	{
		i = 0;
		if (((t_cmd *)current->content)->cmd)
		{
			while (((t_cmd *)current->content)->cmd[i])
				free(((t_cmd *)current->content)->cmd[i++]);
			free(((t_cmd *)current->content)->cmd);
		}
		if (((t_cmd *)current->content)->path)
			free(((t_cmd *)current->content)->path);
		current = current->next;
	}
	ft_lstclear(&cmd_list, free);
}

void	close_fds(t_config *c)
{
	t_list	*current;
	t_cmd	*cmd;

	current = c->cmd_list;
	while (current)
	{
		cmd = current->content;
		if (cmd->io.in != STDIN_FILENO && cmd->io.in > -1)
			close(cmd->io.in);
		if (cmd->io.out != STDOUT_FILENO && cmd->io.out > -1)
			close(cmd->io.out);
		current = current->next;
	}
	c->nb_pipe = 0;
}

void	clean(t_config *c)
{
	close_fds(c);
	clean_cmd_list(c->cmd_list);
	ft_lstclear(&c->tokens, free);
	free(c->command_line);
}

void	exit_failure(t_config *c, char *err_string, int is_errno)
{
	if (is_errno)
		perror(err_string);
	else
		ft_putstr_fd(err_string, 2);
	clean(c);
	exit(g_return);
}
