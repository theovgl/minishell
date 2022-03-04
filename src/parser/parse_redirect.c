/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:13:52 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/03 16:09:56 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(t_list *list)
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

int	parse_redirect(t_list *list, t_cmd *cmd)
{
	t_list	*current;

	current = list;
	if (check_redirection(current) == FAILURE)
		return (FAILURE);
	else
	{
		if (current->type == LESS)
		{
			current = current->next;
			cmd->io.in = open((char *)current->content, O_RDONLY);
			if (cmd->io.in < 0)
				return (FAILURE);
		}
		else if (current->type == GREAT)
		{
			current = current->next;
			cmd->io.out = open((char *)current->content,
					O_TRUNC | O_RDWR | O_CREAT, 00644);
			if (cmd->io.out < 0)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
