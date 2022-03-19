/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:21:55 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/19 16:42:57 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_delimiter(char *line, char *delimiter)
{
	if (ft_strlen(line) > ft_strlen(delimiter))
		return (0);
	else if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
		return (1);
	return (0);
}

void	parse_here_doc(t_config *c, t_list **list, int fd[2])
{
	char	*buff;
	char	*tmp;
	char	*limit;

	g_global.ret = 0;
	limit = ft_strdup((*list)->content);
	buff = readline("> ");
	while (buff && check_delimiter(buff, limit) == 0)
	{
		if (buff == NULL)
			break ;
		tmp = translator(c, buff);
		buff = ft_strjoin(tmp, "\n");
		free(tmp);
		write(fd[1], buff, ft_strlen(buff));
		free(buff);
		buff = readline("> ");
	}
	close(fd[1]);
	free(limit);
}

static void	here_doc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	g_global.ret = 130;
}

void	chatterton(t_config *c, t_cmd *cmd)
{
	handle_tokens_errors(cmd);
	free_path(c);
	ft_lstclear(&c->env, free);
	exit_failure(c, "", 0);
}

int	create_here_doc(t_config *c, t_list **list, t_cmd *cmd)
{
	int		fd[2];
	int		pid;
	int		status;

	if (pipe(fd) < 0)
		exit_failure(c, "Pipe", 1);
	heredoc_fd_manager(cmd, fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		close(cmd->io.in);
		signal(SIGINT, &here_doc_sigint);
		parse_here_doc(c, list, fd);
		chatterton(c, cmd);
	}
	wait(&status);
	close(fd[1]);
	signal(SIGINT, &handle_sigint);
	if (WSTOPSIG(status) != 0)
		return (FAILURE);
	return (SUCCESS);
}
