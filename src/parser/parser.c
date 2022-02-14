/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:35:46 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/14 16:31:34 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_config *c)
{
	c->tokens.prev = NULL;
	c->tokens.type = WORD;
	c->tokens.content = "ls";
	c->tokens.next = ft_lstnew("-l");
	c->tokens.next->type = WORD;
	c->tokens.next->next = ft_lstnew("|");
	c->tokens.next->next->type = PIPE;
	c->tokens.next->next->next = ft_lstnew("/usr/bin/cat");
	c->tokens.next->next->next->type = WORD;
	c->tokens.next->next->next->next = NULL;
}

int	parser(t_config *c)
{
	int	i;

	i = 0;
	init_list(c);
	c->cmd_list = NULL;
	if (parse_env(c))
	{
		printf("PATH not found\n");
		return (1);
	}
	parse_tokens(c);
	return (0);
}
