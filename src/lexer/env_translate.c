/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:50:03 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/15 21:39:34 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief is_var find and return the line where the variable is define in env
 *
 * @param c
 * @param line
 * @return char*
 */
char	*is_var(t_config *c, char *line)
{
	t_list	*current;
	int		i;

	current = c->env;
	if (!line[0])
		return (NULL);
	while (current)
	{
		i = 0;
		while (line[i] && ((char *)(current->content))[i] \
		&& line[i] == ((char *)(current->content))[i])
			i++;
		if (!ft_isalnum(line[i]) && ((char *)(current->content))[i] == '=')
			return (current->content);
		current = current->next;
	}
	if (line[0] == '?')
		return (ft_itoa(g_return));
	return (NULL);
}

/**
 * @brief for a given name find_def return the definition found in env
 *
 * @param c
 * @param line
 * @return char*
 */
char	*find_def(t_config *c, char *line)
{
	int		i;
	int		j;
	char	*def;
	char	*env_line;

	env_line = is_var(c, line);
	if (env_line == NULL || line[0] == '?')
		return (env_line);
	i = 0;
	while (env_line[i] != '=')
		i++;
	i++;
	def = malloc(sizeof(char *) * ft_strlen(env_line) + 1);
	if (def == NULL)
		exit_failure(c, "Malloc failed", 1);
	j = 0;
	while (env_line[i])
	{
		def[j] = env_line[i];
		j++;
		i++;
	}
	def[j] = 0;
	return (def);
}

/**
 * @brief dollar handler replace the current variable to its definition
 * and return an expanded new_line
 *
 * @param c
 * @param i
 * @param line
 * @param new_line
 * @return char*
 */
static char	*dollar_handler(t_config *c, int *i, char *line, char *new_line)
{
	int		j;
	char	*def;
	char	*tmp;

	def = find_def(c, &line[*i]);
	j = 0;
	if (line[*i + j] == '?')
		j++;
	else
	{
		while (ft_isalnum(line[*i + j]) || line[*i + j] == '_' || line[*i + j] == '-')
			j++;
	}
	if (def)
	{
		tmp = ft_strjoin(def, &line[*i + j]);
		free(def);
	}
	else
		tmp = ft_strdup(&line[*i + j]);
	line[--*i] = 0;
	if (new_line)
		free(new_line);
	new_line = ft_strjoin(line, tmp);
	free(tmp);
	free(line);
	return (new_line);
}

static int	single_quote(char *line, int i)
{
	if (line[i] == '\'')
	{
		i++;
		while (line[i] && line[i] != '\'')
			i++;
		i--;
	}
	return (i);
}

/**
 * @brief translator replace all the local variables with their value
 *
 * @param c
 * @param line
 * @return char*
 */
char	*translator(t_config *c, char *line)
{
	int		i;
	char	*new_line;

	if (!line)
		return (NULL);
	new_line = ft_strdup(line);
	i = 0;
	while (line[i])
	{
		i = single_quote(line, i);
		if (line[i] == '$' && line[i + 1] && ft_isalpha(line[i + 1]))
		{
			i++;
			new_line = dollar_handler(c, &i, line, new_line);
			return (translator(c, new_line));
		}
		else
			i++;
	}
	free(line);
	return (new_line);
}
