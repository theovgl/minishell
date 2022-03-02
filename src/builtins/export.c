/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:20:25 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/01 23:36:34 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	j = 0;
	word = malloc(sizeof(char *) * i + 1);
	if (!word)
		return (NULL);
	while (j < i)
	{
		word[j] = s[j];
		j++;
	}
	word[i] = 0;
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
	def[i] = 0;
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
		if (((char *)(current->content))[i] == '=')
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
	if (i == -1)
		return (FAILURE);
	word = get_word(s, word, i);
	if (!word)
		return (FAILURE);
	def = get_def(s, def, i + 1);
	if (modify_in_env(c, word, def) == FAILURE)
		add_in_env(c, word, def);
	return (SUCCESS);
}

// int main(int ac, char *av[], char *ep[])
// {
// 	t_config	c;
// 	char 		*s1 = "TEST=vieux";
// 	char 		*s2[] = {"PWD", "TEST", NULL};
//
// 	(void)ac;
// 	(void)av;
// 	ft_env(&c, ep);
// 	export(&c, s1);
// 	print_env(&c);
// 	unset(&c, s2);
// 	print_env(&c);
// 	return 0;
// }