/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/03 19:39:43 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config	c;

	if (init(&c, envp) == FAILURE)
		return (clean_exit(ERR_INIT));
	handle_signal();
	c.command_line = readline("minishell$> ");
	c.command_line = translator(&c, c.command_line);
	if (c.command_line == NULL)
		printf("exit\n");
	while (c.command_line != NULL)
	{
		add_history(c.command_line);
		if (lexer(&c) != SUCCESS)
			return (clean_exit(ERR_LEXER));
		parser(&c);
		c.command_line = readline("minishell$> ");
	}
	free(c.command_line);
	return (SUCCESS);
}
