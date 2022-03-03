/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:16:12 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/03 04:52:15 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief add a new node in the env list
 * the content is a string that looks like: word=def
 *
 * @param c
 * @param word
 * @param def
 */
void	add_in_env(t_config *c, char *word, char *def)
{
	t_list	*tmp;
	char	*tofree;

	tofree = ft_strjoin(word, "=");
	tmp = ft_lstnew(tofree);
	tmp->content = ft_strjoin(tmp->content, def);
	free(tofree);
	free(word);
	free(def);
	ft_lstadd_back(&c->env, tmp);
}

/**
 * @brief copies the *envp[] in a linked list
 *
 * @param c
 * @param ep
 * @return int
 */
int	ft_env(t_config *c, char *ep[])
{
	int		i;
	t_list	*tmp;

	i = 0;
	if (!ep[i])
		return (FAILURE);
	c->env = ft_lstnew(ep[i++]);
	while (ep[i])
	{
		tmp = ft_lstnew(ep[i]);
		tmp->content = ft_strdup(ep[i]);
		ft_lstadd_back(&c->env, tmp);
		i++;
	}
	return (SUCCESS);
}

void	print_env(t_config *c)
{
	t_list	*current;

	current = c->env;
	while (current)
	{
		printf("%s\n", (char *)(current->content));
		current = current->next;
	}
}
