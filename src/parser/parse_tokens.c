/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:05:59 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/18 01:04:12 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->io.in = STDIN_FILENO;
	new_cmd->io.out = STDOUT_FILENO;
	new_cmd->path = NULL;
	return (new_cmd);
}

void	handle_tokens_errors(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		if (cmd->path)
			free(cmd->path);
		if (cmd->cmd)
		{
			if (cmd->cmd[i])
			{
				while (cmd->cmd[i])
					free(cmd->cmd[i++]);
			}
			free(cmd->cmd);
		}
		if (cmd)
			free(cmd);
	}
}

static	int	isredir(int type)
{
	if (type == LESS || type == GREAT
		|| type == LLESS || type == GGREAT)
	{
		return (1);
	}
	else
		return (0);
}

static	int	do_the_trick(t_config *c, t_list *current, t_cmd *cmd, int p_input)
{
	while (current)
	{
		if (current->type == WORD)
			parse_word(c, &current, cmd);
		else if (isredir(current->type))
		{
			if (parse_redirect(c, &current, cmd) == FAILURE)
			{
				handle_tokens_errors(cmd);
				return (FAILURE);
			}
		}
		else if (current && current->type == PIPE)
		{
			p_input = parse_pipe(c, &current, cmd, p_input);
			add_cmd_to_list(c, cmd);
			cmd = init_cmd();
		}
		else
			current = current->next;
	}
	if (p_input)
		cmd->io.in = p_input;
	add_cmd_to_list(c, cmd);
	return (SUCCESS);
}

/**
 * @brief Parse each token comming from the lexer
 */
int	parse_tokens(t_config *c, t_list *tokens_list)
{
	t_list	*current;
	t_cmd	*cmd;
	int		pipe_input;

	current = tokens_list;
	cmd = init_cmd();
	pipe_input = 0;
	if (!cmd)
		return (FAILURE);
	if (do_the_trick(c, current, cmd, pipe_input) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
