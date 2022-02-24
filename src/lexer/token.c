/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:24:36 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/24 15:24:37 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_node(t_config *c, char *content, int type)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	new_node->type = type;
	if (c->first_node == NULL)
	{
		c->first_node = ft_lstnew(content);
		c->first_node->type = type;
	}
	else
	{
		ft_lstadd_back(&c->first_node, new_node);
		ft_lstlast(c->first_node)->type = type;
	}
	return (SUCCESS);
}

// add_token takes a portion of the command line and a type of token.
// add_token save the portion in the chained list.
// add_token fill c.type accordingly.
int	add_token(t_config *c, int start, int end, int type)
{
	int		i;
	char	*content;
	t_list	*new_node;

	i = 0;
	content = malloc(sizeof(char) * (end - start + 2));
	if (content == NULL)
		return (FAILURE);
	while (start + i <= end)
	{
		content[i] = c->command_line[start + i];
		i++;
	}
	content[i] = '\0';
	create_node(c, content, type);
	return (SUCCESS);
}
