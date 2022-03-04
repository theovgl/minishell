/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 19:31:41 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_on_success(t_config *c)
{
	t_list	*current;
	t_cmd	*cmd;
	int		i;

	current = c->cmd_list;
	while (current)
	{
		i = 0;
		while (((t_cmd *)current->content)->cmd[i])
		{
			free(((t_cmd *)current->content)->cmd[i]);
			i++;
		}
		free(((t_cmd *)current->content)->cmd);
		free(((t_cmd *)current->content)->path);
		current = current->next;
	}
	ft_lstclear(&c->cmd_list, free);
	ft_lstclear(&c->tokens, free);
	free(c->command_line);
}

int	main(int argc, char **argv, char **envp)
{
	t_config	c;

	if (init(&c, envp) == FAILURE)
		return (clean_exit(ERR_INIT));
	handle_signal();
	c.command_line = readline("minishell$> ");
	while (c.command_line != NULL)
	{
		c.command_line = translator(&c, c.command_line);
		add_history(c.command_line);
		if (lexer(&c) != SUCCESS)
			return (clean_exit(ERR_LEXER));
		parser(&c);
printf("OK\n");
		exec(&c, envp);
		clean_on_success(&c);
		c.command_line = readline("minishell$> ");
	}
	ft_lstclear(&c.env, free);
	free(c.command_line);
	return (SUCCESS);
}
