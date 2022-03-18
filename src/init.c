/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:04:51 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/18 17:13:21 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_config *c, char **ep)
{
	g_global.ret = 0;
	c->env = NULL;
	c->path = NULL;
	c->command_line = NULL;
	c->tokens = NULL;
	c->cmd_list = NULL;
	c->nb_pipe = 0;
	if (ft_env(c, ep) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
