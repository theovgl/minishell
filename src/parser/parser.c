/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:35:46 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/25 13:42:10 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_config *c)
{
	c->cmd_list = NULL;
	if (parse_env(c) == FAILURE)
	{
		printf("PATH not found\n");
		return (FAILURE);
	}
	parse_tokens(c);
	return (SUCCESS);
}
