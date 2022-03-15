/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:35:46 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/15 20:58:16 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_path(t_config *c)
{
	int	i;

	i = 0;
	while (c->path[i])
	{
		free(c->path[i]);
		i++;
	}
	free(c->path);
	c->path = NULL;
}

int	parser(t_config *c)
{
	c->cmd_list = NULL;
	if (parse_env(c) == FAILURE)
	{
		printf("PATH not found\n");
		return (FAILURE);
	}
	if (parse_tokens(c, c->tokens) == FAILURE)
	{
		free_path(c);
		return (FAILURE);
	}
	free_path(c);
	return (SUCCESS);
}
