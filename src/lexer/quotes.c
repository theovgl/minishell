/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:31:00 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/07 18:23:28 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	overwrite_quotes(t_config *c, int i)
{
	while (c->command_line[i + 1])
	{
		c->command_line[i] = c->command_line[i + 1];
		i++;
	}
	c->command_line[i] = 0;
	return (i);
}

// Takes the position 'i' of the command line.
// Put |, ' and " in the chained list.
// Returns the new position 'i'.
int	ft_isquote(t_config *c, int i)
{
	int		j;
	char	q;

	j = 0;
	q = c->command_line[i];
	if (q == '\"' || q == '\'')
	{
		j += overwrite_quotes(c, i + j);
	}
	else
		return (i);
	j = 0;
	while (c->command_line[i + j] != q && c->command_line[i + j])
		j++;
	if (!j && c->command_line[i + j] != q)
		return (i);
	overwrite_quotes(c, i + j);
	i += j;
	return (i);
}
