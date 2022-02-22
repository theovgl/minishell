/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/14 12:18:29 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	// char *buff;
	t_config	c;
	if (init(&c) == FAILURE)
		return (clean_exit(ERR_INIT));
	handle_signal();
	c.command_line = readline("$> ");
	while (c.command_line != NULL)
	{
		printf("COMMAND LINE IS: %s\n", c.command_line);
		if (lexer(&c) != SUCCESS)
			return (clean_exit(ERR_LEXER));
		while (c.first_node)
		{
			printf("content: '%s'\n", (char *)c.first_node->content);

			if (c.first_node->type == SUCCESS)
			printf("type: SUCCESS\n");
			if (c.first_node->type == FAILURE)
			printf("type: FAILURE\n");
			if (c.first_node->type == WORD)
			printf("type: WORD\n");
			if (c.first_node->type == GREAT)
			printf("type: GREAT\n");
			if (c.first_node->type == GGREAT)
			printf("type: GGREAT\n");
			if (c.first_node->type == SUCCESS)
			printf("type: SUCCESS\n");
			if (c.first_node->type == LESS)
			printf("type: LESS\n");
			if (c.first_node->type == LLESS)
			printf("type: LLESS\n");
			if (c.first_node->type == PIPE)
			printf("type: PIPE\n");
			if (c.first_node->type == SQUOTE)
			printf("type: SQUOTE\n");
			if (c.first_node->type == DQUOTE)
			printf("type: DQUOTE\n");
			if (c.first_node->type == DOLLAR)
			printf("type: DOLLAR\n");
			if (c.first_node->type == QMARK)
			printf("type: QMARK\n");

			c.first_node = c.first_node->next;
		}
		c.command_line = readline("$> ");
	}
	return (clean_exit(SUCCESS));
}
