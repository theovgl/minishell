/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:13:52 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/01 20:27:21 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirect(t_list *list, t_cmd *cmd)
{
	t_list	*current;

	current = list;
	if (current->type == LESS)
	{
		if (current->next)
		{
			current = current->next;
			cmd->io.in = open((char *)current->content, O_RDONLY);
			if (cmd->io.in < 0)
				return ;
		}
	}
	else if (current->type == GREAT)
	{
		if (current->next)
		{
			current = current->next;
			cmd->io.out = open((char *)current->content,
					O_TRUNC | O_RDWR | O_CREAT, 00644);
			if (cmd->io.out < 0)
				return ;
		}
	}
}
