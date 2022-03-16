/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:13:52 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/16 21:33:30 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_token(t_list *list)
{
	t_list	*current;

	current = list;
	if (!current->next)
	{
		ft_putstr_fd("Syntax error near unexpected token '", STDERR_FILENO);
		ft_putstr_fd(current->content, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		g_return = 2;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_here_doc(t_config *c, t_list **list, t_cmd *cmd)
{
	char	*readline_buf;
	char	*tmp;
	char	*limit;
	int		doc[2];

	if (pipe(doc) < 0)
		exit_failure(c, "Pipe", 1);
	*list = (*list)->next;
	limit = ft_strdup((*list)->content);
	readline_buf = readline("> ");
	while (readline_buf && ft_strncmp(readline_buf, limit, ft_strlen(readline_buf)))
	{
		if (readline_buf == NULL)
			break ;
		tmp = translator(c, readline_buf);
		readline_buf = ft_strjoin(tmp, "\n");
		free(tmp);
		write(doc[1], readline_buf, ft_strlen(readline_buf));
		free(readline_buf);
		readline_buf = readline("> ");
	}
	cmd->io.in = doc[0];
	free(limit);
	close(doc[1]);
}

int	parse_double_chevrons(t_config *c, t_list **list, t_cmd *cmd)
{
	if ((*list)->type == LLESS)
		parse_here_doc(c, list, cmd);
	else if ((*list)->type == GGREAT)
	{
		(*list) = (*list)->next;
		cmd->io.out = open((char *)(*list)->content,
				O_APPEND | O_CREAT | O_RDWR, 00777);
	}
	if (cmd->io.in < 0 || cmd->io.out < 0)
	{
		g_return = errno;
		perror((*list)->content);
		return (FAILURE);
	}
	(*list) = (*list)->next;
	return (SUCCESS);
}

int	parse_redirect(t_config *c, t_list **list, t_cmd *cmd)
{
	if (check_token(*list) == FAILURE)
		return (FAILURE);
	if ((*list)->type == LLESS || (*list)->type == GGREAT)
		return (parse_double_chevrons(c, list, cmd));
	else
	{
		if ((*list)->type == LESS)
		{
			(*list) = (*list)->next;
			cmd->io.in = open((char *)(*list)->content, O_RDONLY);
		}
		else if ((*list)->type == GREAT)
		{
			(*list) = (*list)->next;
			cmd->io.out = open((char *)(*list)->content,
					O_TRUNC | O_RDWR | O_CREAT, 00777);
		}
		if (cmd->io.in < 0 || cmd->io.out < 0)
		{
			g_return = errno;
			perror((*list)->content);
			return (FAILURE);
		}
	}
	(*list) = (*list)->next;
	return (SUCCESS);
}
