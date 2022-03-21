/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:08:37 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/21 10:22:30 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add command and arguments to the commands list
 */
void	add_cmd_to_list(t_config *c, t_cmd *cmd)
{
	t_list	*to_add;

	if (c->cmd_list == NULL)
		c->cmd_list = ft_lstnew(cmd);
	else
	{
		to_add = ft_lstnew(cmd);
		ft_lstadd_back(&c->cmd_list, to_add);
	}
}

int	check_tokens(t_list *list)
{
	t_list	*current;
	int		i;

	current = list;
	i = 0;
	while (current)
	{
		if ((isredir(current->type)
				&& (!current->next || current->next->type != WORD))
			|| (current->type == PIPE && !current->next) ||
			(current->type == PIPE && i == 0))
		{
			ft_putstr_fd("Syntax error near unexpected token '",
				STDERR_FILENO);
			ft_putstr_fd(current->content, STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			g_global.ret = 2;
			return (FAILURE);
		}
		current = current->next;
		i++;
	}
	return (SUCCESS);
}

int	isredir(int type)
{
	if (type == LESS || type == GREAT
		|| type == LLESS || type == GGREAT)
	{
		return (1);
	}
	else
		return (0);
}
