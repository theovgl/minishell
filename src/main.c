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
		// while (c.first_node)
		// {
		// 	printf("content: %s\n", (char *)c.first_node->content);
		// 	printf("type: %d\n", c.first_node->type);
		// 	c.first_node = c.first_node->next;
		// }
		c.command_line = readline("$> ");
	}
	return (clean_exit(SUCCESS));
}
