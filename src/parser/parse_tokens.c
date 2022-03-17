/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:05:59 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/17 20:12:43 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add command and arguments to the commands list
 */
void	add_cmd_to_list(t_config *c, t_cmd *cmd)
{
	t_list	*to_add;

	if (c->cmd_list == NULL)
		c->cmd_list = ft_lstnew(cmd);
	else
	{
		to_add = ft_lstnew(cmd);
		ft_lstadd_back(&c->cmd_list, to_add);
	}
}

void	print_cmd(t_config *c)
{
	int		i;
	int		j;
	t_list	*current;

	j = 0;
	i = 0;
	current = c->cmd_list;
	while (current && ((t_cmd *)(current->content))->cmd)
	{
		i = 0;
		while (((t_cmd *)(current->content))->cmd[i])
		{
			printf("%s\n", ((t_cmd *)(current->content))->cmd[i]);
			i++;
		}
		printf("input: %i\n", ((t_cmd *)current->content)->io.in);
		printf("output: %i\n", ((t_cmd *)current->content)->io.out);
		j++;
		current = current->next;
	}
}

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
	while (current)
	{
		if (current->type == WORD)
			parse_word(c, &current, cmd);
		else if (current->type == LESS || current->type == GREAT
			|| current->type == LLESS || current->type == GGREAT)
		{
			if (parse_redirect(c, &current, cmd) == FAILURE)
			{
				handle_tokens_errors(cmd);
				return (FAILURE);
			}
		}
		else if (current && current->type == PIPE)
		{
			pipe_input = parse_pipe(c, &current, cmd, pipe_input);
			add_cmd_to_list(c, cmd);
			cmd = init_cmd();
		}
		else
			current = current->next;
	}
	if (pipe_input)
		cmd->io.in = pipe_input;
	add_cmd_to_list(c, cmd);
	return (SUCCESS);
}
