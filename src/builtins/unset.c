/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:06:16 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/15 11:59:07 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_id(t_config *c, char *id)
{
	int	i;

	i = 0;
	while (id[i])
	{
		if (i == 0 && ft_isalpha(id[i]) == 0 && id[i] != '_')
		{
			printf("unset: '%s': not a valid identifier\n", id);
			g_return = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief unset the list of variables *word[]
 * nothing happens if one of the words is not in env
 *
 * @param c
 * @param word
 * @return int
 */
void	unset(t_config *c, char *word[])
{
	t_list	*current;
	t_list	*tmp;
	int		i;
	int		j;

	j = 1;
	if (!word[j])
	{
		g_return = 0;
		return ;
	}
	while (word[j] && check_id(c, word[j]) == 0)
	{
		current = c->env;
		while (current)
		{
			i = 0;
			while (word[j][i] == ((char *)(current->content))[i])
				i++;
			if (!word[j][i] && ((char *)(current->content))[i] == '=')
			{
				tmp = current;
				current = current->prev;
				current->next = tmp->next;
				free(tmp->content);
				free(tmp);
			}
			current = current->next;
		}
		j++;
	}
	g_return = 0;
}
