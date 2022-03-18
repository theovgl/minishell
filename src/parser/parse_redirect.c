/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:13:52 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/18 14:24:10 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_token(t_list *list)
{
	t_list	*current;

	current = list;
	if (!current->next || current->next->type != WORD)
	{
		ft_putstr_fd("Syntax error near unexpected token '", STDERR_FILENO);
		ft_putstr_fd(current->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		g_return = 2;
		return (FAILURE);
	}
	return (SUCCESS);
}

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
		g_return = errno;
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
		cmd->io.in = open((char *)(*list)->content, O_RDONLY);
	}
	else if ((*list)->type == GREAT)
	{
		(*list) = (*list)->next;
		cmd->io.out = open((char *)(*list)->content,
				O_TRUNC | O_RDWR | O_CREAT, 00777);
	}
	if (cmd->io.in < 0 || cmd->io.out < 0)
	{
		g_return = errno;
		perror((*list)->content);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_redirect(t_config *c, t_list **list, t_cmd *cmd)
{
	if (check_token(*list) == FAILURE)
		return (FAILURE);
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
