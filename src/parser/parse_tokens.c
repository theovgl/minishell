/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 15:05:59 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/14 17:26:56 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Save the command path in the cmd structure
 *
 * @param c
 * @param cmd
 * @return int
 */
static int	get_cmd_path(t_config *c, t_cmd *cmd, char *to_check)
{
	int		i;
	char	*temp;

	i = 0;
	while (c->env[i] && to_check != NULL && to_check[0] != '\0')
	{
		temp = ft_strjoin(c->env[i], to_check);
		if (access(temp, F_OK) == 0)
		{
			cmd->path = ft_strdup(temp);
			free(temp);
			return (1);
		}
		free(temp);
		i++;
	}
	if (to_check != NULL)
		cmd->path = ft_strdup(to_check);
	else
		cmd->path = NULL;
	return (0);
}

int	get_cmd_size(t_list *node)
{
	t_list	*current;
	int		i;

	i = 0;
	current = node;
	while (current != NULL && current->type == WORD)
	{
		i++;
		current = current->next;
	}
	return (i);
}

static t_cmd	parse_word(t_config *c, t_list *list, int size)
{
	t_list	*current;
	t_cmd	new;
	int		i;

	i = 0;
	current = list;
	new.cmd = malloc(sizeof(char *) * (size + 1));
	// if (new.cmd == NULL)
	// 	return ;
	while (current && current->type == WORD && current->content)
	{
		new.cmd[i++] = ft_strdup(current->content);
		current = current->next;
	}
	new.cmd[i] = NULL;
	get_cmd_path(c, &new, new.cmd[0]);
	return (new);
}

/**
 * @brief Add command and arguments to the commands list
 *
 * @param c
 * @param cmd
 */
static void	add_cmd_to_list(t_config *c, t_cmd *cmd)
{
	t_list	*to_add;

	to_add = ft_lstnew(cmd);
	if (c->cmd_list == NULL)
		c->cmd_list = ft_lstnew(cmd);
	else
		ft_lstadd_back(&c->cmd_list, to_add);
}

/**
 * @brief Parse each token comming from the lexer
 *
 * @param c
 */
void	parse_tokens(t_config *c)
{
	t_list	*current;
	t_cmd	cmd;
	int		size;

	current = &c->tokens;
	while (current)
	{
		if (current->type == WORD)
		{
			size = get_cmd_size(current);
			cmd = parse_word(c, current, size);
			while (current && current->type == WORD)
				current = current->next;
			add_cmd_to_list(c, &cmd);
		}
		else
			current = current->next;
	}
}
