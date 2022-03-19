/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:06:16 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/19 16:54:47 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_id(char *id)
{
	if (!id)
	{
		g_global.ret = 0;
		return (0);
	}
	if (!ft_isvariable(id))
	{
		printf("unset: '%s': not a valid identifier\n", id);
		g_global.ret = 1;
		return (1);
	}
	g_global.ret = 0;
	return (0);
}

static	t_list	*suppr_node(t_list *current)
{
	t_list	*tmp;

	tmp = current;
	current = current->prev;
	current->next = tmp->next;
	if (current->next)
		current->next->prev = current;
	free(tmp->content);
	free(tmp);
	return (current);
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
	int		i;
	int		j;

	j = 1;
	while (word[j] && check_id(word[j]) == 0)
	{
		current = c->env;
		while (current)
		{
			i = 0;
			while (word[j][i] == ((char *)(current->content))[i])
				i++;
			if (!word[j][i] && ((char *)(current->content))[i] == '=')
				current = suppr_node(current);
			current = current->next;
		}
		j++;
	}
}
