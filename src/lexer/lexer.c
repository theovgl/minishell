/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:08:26 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 23:58:35 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Takes the position 'i' of the command line.
// Put <, <<, > and >> in the chained list.
// Returns the new position 'i'.
int	ft_islessgreat(t_config *c, int i)
{
	if (c->command_line[i] == '<' && c->command_line[i + 1] != '<')
	{
		if (add_token(c, i, i, LESS) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '<' && c->command_line[i + 1] == '<')
	{
		if (add_token(c, i, i + 1, LLESS) == FAILURE)
			return (-1);
		i += 2;
	}
	if (c->command_line[i] == '>' && c->command_line[i + 1] != '>')
	{
		if (add_token(c, i, i, GREAT) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '>' && c->command_line[i + 1] == '>')
	{
		if (add_token(c, i, i + 1, GGREAT) == FAILURE)
			return (-1);
		i += 2;
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put |, ' and " in the chained list.
// Returns the new position 'i'.
int	ft_isquote(t_config *c, int i)
{
	int		j;
	int		k;
	char	q;
	int		type;

	j = 0;
	q = c->command_line[i];
	if (q == '\"' || q == '\'')
	{
		while (c->command_line[i + j + 1])
		{
			c->command_line[i + j] = c->command_line[i + j + 1];
			j++;
		}
		c->command_line[i + j] = 0;
	}
	else
		return (i);
	j = 0;
	while (c->command_line[i + j] != q && c->command_line[i + j])
		j++;
	if (!j)
		return (i);
	k = 0;
	while (c->command_line[i + j + k + 1])
	{
		c->command_line[i + j + k] = c->command_line[i + j + k + 1];
		k++;
	}
	c->command_line[i + j + k] = 0;
	i += j;
	return (i);
}

// Takes the position 'i' of the command line.
// Put $ and ? in the chained list.
// Returns the new position 'i'.
int	ft_isdollar_qmark_pipe(t_config *c, int i)
{
	if (c->command_line[i] == '$')
	{
		if (add_token(c, i, i, DOLLAR) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '?')
	{
		if (add_token(c, i, i, QMARK) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '|')
	{
		if (add_token(c, i, i, PIPE) == FAILURE)
			return (-1);
		i++;
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put a word in the chained list.
// If '-' precede the word, the type is set as ARG.
// Returns the new position 'i'.
int	ft_isword(t_config *c, int i)
{
	int	j;
	int	k;

	j = 0;
	while (c->command_line[i + j] && \
	c->command_line[i + j] != '?' && \
	c->command_line[i + j] != '$' && \
	c->command_line[i + j] != '<' && \
	c->command_line[i + j] != '>' && \
	c->command_line[i + j] != '|' && \
	!ft_isspace(c->command_line[i + j]))
	{
		k = ft_isquote(c, i + j) - i - j;
		if (!k)
			j++;
		else
			j += k;
	}
	if (!j)
		return (i);
	if (add_token(c, i, i + j - 1, WORD) == FAILURE)
		return (clean_exit(ERR_ADD_TOKEN));
	return (i + j);
}

// The lexer takes the char* resulting of the readline.
// It suposedly contains the commands that minishell has to execute.
// The lexer set apart every part of the command list
// and save them as tokens in a linked chain.
int	lexer(t_config *c)
{
	int	i;

	i = 0;
	while (c->command_line[i])
	{
		while (ft_isspace(c->command_line[i]))
			i++;
		if (c->command_line[i])
			i = ft_isword(c, i);
		if (i == -1)
			return (FAILURE);
		if (c->command_line[i])
			i = ft_islessgreat(c, i);
		if (i == -1)
			return (FAILURE);
		if (c->command_line[i])
			i = ft_isdollar_qmark_pipe(c, i);
		if (i == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}
