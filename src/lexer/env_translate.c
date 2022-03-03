/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:50:03 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/03 20:50:07 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (NULL);
}

char	*find_def(t_config *c, char *line)
{
	int		i;
	int		j;
	char	*def;
	char	*env_line;

	env_line = is_var(c, line);
	if (env_line == NULL)
		return (NULL);
	i = 0;
	while (env_line[i] != '=')
		i++;
	i++;
	def = malloc(sizeof(char *) * ft_strlen(env_line) + 1);
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

char	*dollar_handler(t_config *c, int *i, char *line, char *new_line)
{
	int		j;
	char	*def;
	char	*tmp;

	def = find_def(c, &line[*i]);
	j = 0;
	while (ft_isalnum(line[*i + j]))
		j++;
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
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '$' && line[i + 1] && !ft_isspace(line[i + 1]))
		{
			i++;
			new_line = dollar_handler(c, &i, line, new_line);
			return (translator(c, new_line));
		}
		i++;
	}
	free(line);
	return (new_line);
}
