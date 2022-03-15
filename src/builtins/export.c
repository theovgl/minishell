/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:20:25 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/14 20:35:12 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief return the position of '='
 * if '=' is not found '-1' is returned
 *
 * @param s
 * @return int
 */
int	find_eq(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	s[i] = 0;
	return (-1);
}

/**
 * @brief Get the word object malloc it and return it as a string
 *
 * @param s
 * @param word
 * @param i
 * @return char*
 */
char	*get_word(char *s, char *word, int i)
{
	int	j;

	if (i == -1)
		return (NULL);
	j = 0;
	word = malloc(sizeof(char *) * i + 1);
	if (!word)
		return (NULL);
	while (j < i)
	{
		if (!ft_isalnum(s[j]))
		{
			printf("%s : not a valid identifier\n", s);
			free(s);
			return (NULL);
		}
		word[j] = s[j];
		j++;
	}
	word[i] = '\0';
	return (word);
}

/**
 * @brief Get the def object malloc it and return it as a string
 *
 * @param s
 * @param def
 * @param i
 * @return char*
 */
char	*get_def(char *s, char *def, int i)
{
	int	j;

	j = i;
	while (s[j])
		j++;
	def = malloc(sizeof(char *) * j - i + 1);
	if (!def)
		return (NULL);
	j = 0;
	while (s[i])
	{
		def[j] = s[i];
		i++;
		j++;
	}
	def[j] = '\0';
	return (def);
}

/**
 * @brief modify the definition of the word
 * if the word is not found nothing happens and FAILURE is returned
 *
 * @param c
 * @param word
 * @param def
 * @return int
 */
int	modify_in_env(t_config *c, char *word, char *def)
{
	t_list	*current;
	char	*tmp;
	int		i;

	current = c->env;
	while (current)
	{
		i = 0;
		while (word && current->content \
			&& word[i] == ((char *)(current->content))[i])
			i++;
		if (!word[i] && ((char *)(current->content))[i] == '=')
		{
			free(current->content);
			tmp = ft_strjoin(word, "=");
			current->content = ft_strjoin(tmp, def);
			free(tmp);
			return (SUCCESS);
		}
		current = current->next;
	}
	return (FAILURE);
}

/**
 * @brief export() set a new or existing variable in the env list
 *
 * @param c
 * @param s
 * @return int
 */
int	export(t_config *c, char *s)
{
	int		i;
	char	*word;
	char	*def;

	word = NULL;
	def = NULL;
	i = find_eq(s);
	word = get_word(s, word, i);
	if (i == -1)
		return (FAILURE);
	if (!word)
		return (FAILURE);
	def = get_def(s, def, i + 1);
	if (modify_in_env(c, word, def) == FAILURE)
		add_in_env(c, word, def);
	free(word);
	free(def);
	return (SUCCESS);
}

int	ft_export(t_config *c, char *tmp[])
{
	int	i;

	i = 1;
	if (!tmp[i])
	{
		print_env(c, 1);
		return (SUCCESS);
	}
	while (tmp[i])
	{
		if(export(c, tmp[i]) == FAILURE)
		{
			g_return = 1;
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
