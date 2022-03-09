/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:05:59 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/09 13:53:40 by tvogel           ###   ########.fr       */
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
	new_cmd->cmd = NULL;
	new_cmd->io.in = STDIN_FILENO;
	new_cmd->io.out = STDOUT_FILENO;
	new_cmd->path = NULL;
	return (new_cmd);
}

static void	handle_error(t_cmd *cmd)
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
int	parse_tokens(t_config *c)
{
	t_list	*current;
	t_cmd	*cmd;

	current = c->tokens;
	cmd = init_cmd();
	while (current)
	{
		if (current->type == WORD)
			parse_word(c, &current, cmd);
		else if (current->type == LESS || current->type == GREAT
			|| current->type == LLESS || current->type == GGREAT)
		{
			if (parse_redirect(&current, cmd) == FAILURE)
			{
				handle_error(cmd);
				return (FAILURE);
			}
		}
		else
			current = current->next;
	}
	add_cmd_to_list(c, cmd);
	return (SUCCESS);
}
