/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:04:51 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/02 22:44:11 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_config *c, char **ep)
{
	c->env = NULL;
	ft_env(c, ep);
	c->last_return = 0;
	c->command_line = NULL;
	c->tokens = NULL;
	return (SUCCESS);
}
