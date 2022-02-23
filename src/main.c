/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:45:04 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/13 16:30:20 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*buffer;
	t_config	c;

	handle_signal();
	buffer = readline("minishell$> ");
	while (buffer != NULL)
	{
		add_history(buffer);
		parser(&c);
		buffer = readline("minishell$> ");
	}
	free(buffer);
	return (SUCCESS);
}
