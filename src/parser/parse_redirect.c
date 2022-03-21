/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:13:52 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/21 10:21:53 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_double_chevrons(t_config *c, t_list **list, t_cmd *cmd)
{
	if ((*list)->type == LLESS)
	{
		*list = (*list)->next;
		if (create_here_doc(c, list, cmd) == FAILURE)
			return (FAILURE);
	}
	else if ((*list)->type == GGREAT)
	{
		(*list) = (*list)->next;
		cmd->io.out = open((char *)(*list)->content,
				O_APPEND | O_CREAT | O_RDWR, 00777);
	}
	if (cmd->io.in < 0 || cmd->io.out < 0)
	{
		g_global.ret = errno;
		perror((*list)->content);
		return (FAILURE);
	}
	(*list) = (*list)->next;
	return (SUCCESS);
}

int	parse_single_chevron(t_list **list, t_cmd *cmd)
{
	if ((*list)->type == LESS)
	{
		(*list) = (*list)->next;
		if (cmd->io.in != STDIN_FILENO)
			close(cmd->io.in);
		cmd->io.in = open((char *)(*list)->content, O_RDONLY);
	}
	else if ((*list)->type == GREAT)
	{
		(*list) = (*list)->next;
		if (cmd->io.out != STDOUT_FILENO)
			close(cmd->io.out);
		cmd->io.out = open((char *)(*list)->content,
				O_TRUNC | O_RDWR | O_CREAT, 00777);
	}
	if (cmd->io.in < 0 || cmd->io.out < 0)
	{
		g_global.ret = errno;
		perror((*list)->content);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_redirect(t_config *c, t_list **list, t_cmd *cmd)
{
	if ((*list)->type == LLESS || (*list)->type == GGREAT)
		return (parse_double_chevrons(c, list, cmd));
	else
	{
		if (parse_single_chevron(list, cmd) == FAILURE)
			return (FAILURE);
	}
	(*list) = (*list)->next;
	return (SUCCESS);
}
/*
void	print_cmd(t_config *c)
{
	int		i;
	int		j;
	t_list	*current;

	j = 0;
	i = 0;
	current = c->cmd_list;
	while (current && ((t_cmd *)(current->content))->cmd)
	{
		i = 0;
		while (((t_cmd *)(current->content))->cmd[i])
		{
			printf("%s\n", ((t_cmd *)(current->content))->cmd[i]);
			i++;
		}
		printf("input: %i\n", ((t_cmd *)current->content)->io.in);
		printf("output: %i\n", ((t_cmd *)current->content)->io.out);
		j++;
		current = current->next;
	}
}
*/
