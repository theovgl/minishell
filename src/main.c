/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/25 15:33:36 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config	c;

	if (init(&c) == FAILURE)
		return (clean_exit(ERR_INIT));
	handle_signal();
	c.command_line = readline("minishell$> ");
	while (c.command_line != NULL)
	{
		add_history(c.command_line);
		if (lexer(&c) != SUCCESS)
			return (clean_exit(ERR_LEXER));
		parser(&c);
		c.command_line = readline("minishell$> ");
	}
	free(buffer);
	return (SUCCESS);
}
