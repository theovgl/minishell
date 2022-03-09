/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/08 19:16:19 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_config	c;
  
	if (init(&c, envp) == FAILURE)
		return (clean_exit(&c, ERR_INIT));
	handle_signal();
	while (1)
	{
		c.command_line = readline("minishell$> ");
		if (c.command_line == NULL)
			break ;
		add_history(c.command_line);
		c.command_line = translator(&c, c.command_line);
		if (lexer(&c) != SUCCESS)
			return (clean_exit(&c, ERR_LEXER));
		else if (parser(&c) == SUCCESS)
			exec(&c, envp);
		clean_on_success(&c);
	}
	printf("exit\n");
	ft_lstclear(&c.env, free);
	free(c.command_line);
	return (SUCCESS);
}
