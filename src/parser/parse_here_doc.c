/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:21:55 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/17 20:03:04 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_here_doc(t_config *c, t_list **list, int fd[2])
{
	char	*readline_buf;
	char	*tmp;
	char	*limit;

	g_return = 0;
	limit = ft_strdup((*list)->content);
	readline_buf = readline("> ");
	while (readline_buf && ft_strncmp(readline_buf, limit, ft_strlen(limit)))
	{
		if (readline_buf == NULL)
			break ;
		tmp = translator(c, readline_buf);
		readline_buf = ft_strjoin(tmp, "\n");
		free(tmp);
		write(fd[1], readline_buf, ft_strlen(readline_buf));
		free(readline_buf);
		readline_buf = readline("> ");
	}
	close(fd[1]);
	free(limit);
}

static void	here_doc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	g_return = 130;
}

int	create_here_doc(t_config *c, t_list **list, t_cmd *cmd)
{
	int		fd[2];
	int		pid;
	int		status;

	if (pipe(fd) < 0)
		exit_failure(c, "Pipe", 1);
	signal(SIGINT, SIG_IGN);
	cmd->io.in = fd[0];
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, &here_doc_sigint);
		parse_here_doc(c, list, fd);
		exit_failure(c, "", 0);
	}
	wait(&status);
	close(fd[1]);
	signal(SIGINT, &handle_sigint);
	if (WSTOPSIG(status) != 0)
	{
		close(fd[0]);
		return (FAILURE);
	}
	return (SUCCESS);
}
