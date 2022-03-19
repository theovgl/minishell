/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/18 23:11:40 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)), char **envp)
{
	t_config	c;

	if (init(&c, envp) == FAILURE)
		exit_failure(&c, "Init failed\n", 0);
	handle_signal();
	while (1)
	{
		g_global.child = 0;
		c.command_line = readline("minimichel$> ");
		if (c.command_line == NULL)
			break ;
		add_history(c.command_line);
		c.command_line = translator(&c, c.command_line);
		if (lexer(&c) != SUCCESS)
			exit_failure(&c, "Lexer failed\n", 0);
		else if (parser(&c) == SUCCESS)
		{
			exec(&c, envp);
		}
		clean(&c);
	}
	printf("exit\n");
	ft_lstclear(&c.env, free);
	free(c.command_line);
	return (g_global.ret);
}
