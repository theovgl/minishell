/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:24:36 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 15:19:19 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_node(t_config *c, char *content, int type)
{
	t_list	*new_node;

	if (c->tokens == NULL)
	{
		c->tokens = ft_lstnew(content);
		c->tokens->type = type;
	}
	else
	{
		new_node = ft_lstnew(content);
		new_node->type = type;
		ft_lstadd_back(&c->tokens, new_node);
		ft_lstlast(c->tokens)->type = type;
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
