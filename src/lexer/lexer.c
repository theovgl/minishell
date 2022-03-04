/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:08:26 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 21:17:55 by tvogel           ###   ########.fr       */
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
	char	q;
	int		type;

	j = 0;
	q = c->command_line[i];
	if (q == '\"')
		type = DQUOTE;
	else if (q == '\'')
		type = SQUOTE;
	else
		return (i);
	if (add_token(c, i, i, type) == FAILURE)
		return (-1);
	i++;
	while (c->command_line[i + j] != q && c->command_line[i + j])
		j++;
	if (!j)
		return (i);
	if (add_token(c, i, i + j - 1, WORD) == FAILURE)
		return (-1);
	i += j;
	if (add_token(c, i, i, type) == FAILURE)
		return (-1);
	return (++i);
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

	j = 0;
	while (c->command_line[i + j] && \
	c->command_line[i + j] != '\"' && \
	c->command_line[i + j] != '\'' && \
	c->command_line[i + j] != '?' && \
	c->command_line[i + j] != '$' && \
	c->command_line[i + j] != '<' && \
	c->command_line[i + j] != '>' && \
	c->command_line[i + j] != '|' && \
	!ft_isspace(c->command_line[i + j]))
		j++;
	if (!j)
		return (i);
	if (add_token(c, i, i + j - 1, WORD) == FAILURE)
		return (clean_exit(c, ERR_ADD_TOKEN));
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
			i = ft_isquote(c, i);
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
