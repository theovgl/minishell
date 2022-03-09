/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:04:51 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/09 23:03:28 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_config *c, char **ep)
{
	c->env = NULL;
	c->path = NULL;
	c->command_line = NULL;
	c->tokens = NULL;
	c->cmd_list = NULL;
	if(ft_env(c, ep) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
