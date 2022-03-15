/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:29:22 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/15 21:21:25 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_config *c, t_list **list, t_cmd *cmd, int pipe_input)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit_failure(c, "Pipe", 1);
	printf("PIPE %i, %i\n", fd[0], fd[1]);
	if (c->nb_pipe == 0 && cmd->io.out == STDOUT_FILENO)
	{
		cmd->io.out = fd[1];
	}
	else if (c->nb_pipe > 0)
	{
		if (pipe_input)
		{
			cmd->io.in = pipe_input;
		}
		cmd->io.out = fd[1];
	}
	c->nb_pipe++;
	*list = (*list)->next;
	return (fd[0]);
}
