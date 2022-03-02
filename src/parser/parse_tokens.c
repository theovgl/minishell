/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:05:59 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/02 13:41:35 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add command and arguments to the commands list
 */
void	add_cmd_to_list(t_config *c, t_cmd *cmd)
{
	t_list	*to_add;

	to_add = ft_lstnew(cmd);
	if (c->cmd_list == NULL)
		c->cmd_list = ft_lstnew(cmd);
	else
		ft_lstadd_back(&c->cmd_list, to_add);
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

/**
 * @brief Parse each token comming from the lexer
 */
void	parse_tokens(t_config *c)
{
	t_list	*current;
	t_cmd	*cmd;

	current = c->tokens;
	c->cmd_list = NULL;
	cmd = init_cmd();
	while (current)
	{
		if (current->type == WORD)
		{
			parse_word(c, current, cmd);
			while (current && current->type == WORD)
				current = current->next;
		}
		else if (current->type == LESS || current->type == GREAT)
		{
			parse_redirect(current, cmd);
			current = current->next->next;
		}
		else if (current->type == PIPE)
			current = current->next;
	}
	add_cmd_to_list(c, cmd);
	print_cmd(c);
}
