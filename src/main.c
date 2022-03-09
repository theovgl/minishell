/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/09 22:58:47 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno;
int	g_pid;

int	main(int argc, char **argv, char **envp)
{
	t_config	c;

	if (init(&c, envp) == FAILURE)
		exit_failure(&c, "Init failed\n", 0);
	handle_signal();
	while (1)
	{
		c.command_line = readline("minimichel$> ");
		if (c.command_line == NULL)
			break ;
		add_history(c.command_line);
		c.command_line = translator(&c, c.command_line);
		if (lexer(&c) != SUCCESS)
			exit_failure(&c, "Lexer failed\n", 0);
		else if (parser(&c) == SUCCESS)
			exec(&c, envp);
		clean(&c);
	}
	printf("exit\n");
	ft_lstclear(&c.env, free);
	free(c.command_line);
	return (g_errno);
}
