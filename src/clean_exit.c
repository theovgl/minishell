/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:24:45 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/07 16:11:17 by tvogel           ###   ########.fr       */
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
}

void	clean_on_success(t_config *c)
{
	close_fds(c);
	clean_cmd_list(c->cmd_list);
	ft_lstclear(&c->tokens, free);
	free(c->command_line);
}

int	clean_exit(t_config *c, int code)
{
	clean_on_success(c);
	if (code == ERR_ADD_TOKEN)
		printf("an error occured while trying to add a new token\n");
	return (code);
}
