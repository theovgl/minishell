/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:13:52 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/09 13:45:56 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_token(t_list *list)
{
	t_list	*current;

	current = list;
	if (!current->next)
	{
		ft_putstr_fd("Syntax error near unexpected token '", STDERR_FILENO);
		ft_putstr_fd(current->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_double_chevrons(t_list **list, t_cmd *cmd)
{
	if ((*list)->type == GGREAT)
	{
		(*list) = (*list)->next;
		cmd->io.out = open((char *)(*list)->content,
				O_APPEND | O_CREAT | O_RDWR, 00777);
	}
	if (cmd->io.in < 0 || cmd->io.out < 0)
	{
		perror((*list)->content);
		return (FAILURE);
	}
	(*list) = (*list)->next;
	return (SUCCESS);
}

int	parse_redirect(t_list **list, t_cmd *cmd)
{
	if (check_token(*list) == FAILURE)
		return (FAILURE);
	if ((*list)->type == LLESS || (*list)->type == GGREAT)
		return (parse_double_chevrons(list, cmd));
	else
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
			perror((*list)->content);
			return (FAILURE);
		}
	}
	(*list) = (*list)->next;
	return (SUCCESS);
}
