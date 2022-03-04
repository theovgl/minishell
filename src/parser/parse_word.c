/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:37:41 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/02 23:04:23 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Save the command path in the cmd structure

 * @return int
 */
static int	get_cmd_path(t_config *c, t_cmd *cmd, char *to_check)
{
	int		i;
	char	*temp;

	i = 0;
	while (c->path[i] && to_check != NULL && to_check[0] != '\0')
	{
		temp = ft_strjoin(c->path[i], to_check);
		if (access(temp, F_OK) == 0)
		{
			cmd->path = ft_strdup(temp);
			free(temp);
			return (FAILURE);
		}
		free(temp);
		i++;
	}
	if (to_check != NULL)
		cmd->path = ft_strdup(to_check);
	else
		cmd->path = NULL;
	return (SUCCESS);
}

/**
 * @brief Return the number of arguments for each command
 * @return int
*/
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

/**
 * @brief Add each WORD token in a new t_cmd
 * @return t_cmd *
*/
void	parse_word(t_config *c, t_list *list, t_cmd *to_fill)
{
	t_list	*current;
	int		i;
	int		size;

	i = 0;
	size = get_cmd_size(list);
	current = list;
	if (is_builtin((char *)current->content))
		to_fill->builtin = 1;
	else
		to_fill->builtin = 0;
	to_fill->cmd = malloc(sizeof(char *) * (size + 1));
	while (current && current->type == WORD && current->content)
	{
		to_fill->cmd[i] = ft_strdup(current->content);
		current = current->next;
		i++;
	}
	to_fill->cmd[i] = NULL;
	get_cmd_path(c, to_fill, to_fill->cmd[0]);
}
