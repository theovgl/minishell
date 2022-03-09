/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:06:16 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/09 12:13:24 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	j = 0;
	while (word[j])
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
}
