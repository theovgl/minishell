/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:49:46 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/18 17:13:21 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path)
{
	char	*error;

	if (chdir(path) == -1)
	{
		error = ft_strjoin("cd: ", path);
		g_global.ret = 1;
		perror(error);
		free(error);
		return (FAILURE);
	}
	g_global.ret = 0;
	return (SUCCESS);
}
