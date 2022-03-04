/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:35:46 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 19:35:44 by abiju-du         ###   ########.fr       */
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
	parse_tokens(c);
	free_path(c);
	return (SUCCESS);
}
