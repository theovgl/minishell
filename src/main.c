/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 21:36:53 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config	c;

	if (init(&c, envp) == FAILURE)
		return (clean_exit(&c, ERR_INIT));
	handle_signal();
	c.command_line = readline("minishell$> ");
	while (c.command_line != NULL)
	{
		c.command_line = translator(&c, c.command_line);
		add_history(c.command_line);
		if (lexer(&c) != SUCCESS)
			return (clean_exit(&c, ERR_LEXER));
		else if (parser(&c) == SUCCESS)
			exec(&c, envp);
		clean_on_success(&c);
		c.command_line = readline("minishell$> ");
	}
	printf("exit\n");
	ft_lstclear(&c.env, free);
	free(c.command_line);
	return (SUCCESS);
}
