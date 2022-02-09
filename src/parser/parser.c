/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:35:46 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/09 17:28:14 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_config *c)
{
	c->tokens.prev = NULL;
	c->tokens.type = WORD;
	c->tokens.content = "ls";
	c->tokens.next = ft_lstnew("-l");
	c->tokens.next->type = ARG;
}

/**
 * Add the final / to the different paths
*/
void	format_path(t_config *c)
{
	int	i;

	i = 0;
	while (c->env[i])
	{
		c->env[i] = ft_strjoin(c->env[i], "/");
		i++;
	}
}

/**
 * Check if the PATH variable is present in the env
 * If the variable exist the function split all the different paths in a char**
*/
int	parse_env(t_config *c)
{
	char	*ret;

	ret = ft_strdup(getenv("PATH"));
	if (ret == NULL)
		return (1);
	c->env = ft_split(ret, ':');
	format_path(c);
	return (0);
}

int	parser(t_config *c)
{
	int	i;

	i = 0;
	init_list(c);
	if (parse_env(c))
	{
		printf("PATH not found\n");
		return (1);
	}
	while (c->env[i])
	{
		printf("%s\n", c->env[i]);
		i++;
	}
	return (0);
}
