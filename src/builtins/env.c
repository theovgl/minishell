/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:16:12 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/09 11:45:22 by abiju-du         ###   ########.fr       */
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
	free(word);
	tmp = ft_lstnew(tofree);
	tmp->content = ft_strjoin(tmp->content, def);
	free(tofree);
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
	char	*current_var;
	t_list	*tmp;

	i = 0;
	if (!ep[i])
		return (FAILURE);
	while (ep[i])
	{
		current_var = ft_strdup(ep[i]);
		if (c->env == NULL)
			c->env = ft_lstnew(current_var);
		else
		{
			tmp = ft_lstnew(current_var);
			ft_lstadd_back(&c->env, tmp);
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief print the env list.
 * if export is not zero it print 'export ' before the line.
 * This feature is used in the export function.
 * 
 * @param c 
 * @param export 
 */
void	print_env(t_config *c, int export)
{
	t_list	*current;

	current = c->env;
	while (current)
	{
		if (export)
			printf("export %s\n", (char *)(current->content));
		else
			printf("%s\n", (char *)(current->content));
		current = current->next;
	}
}

char	*getpath(t_config *c)
{
	int		i;
	char	*word;
	char	*def;
	t_list	*current;

	word = "PATH";
	def = NULL;
	current = c->env;
	while (current)
	{
		i = 0;
		while (current->content && word[i] == ((char *)(current->content))[i])
			i++;
		if (!word[i] && ((char *)(current->content))[i] == '=')
			return (get_def(current->content, def, i + 1));
		current = current->next;
	}
	return (NULL);
}