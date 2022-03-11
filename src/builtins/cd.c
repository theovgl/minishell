/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:49:46 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/10 15:02:46 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path)
{
	char	*error;

	if (chdir(path) == -1)
	{
		error = ft_strjoin("cd: ", path);
		perror(error);
		free(error);
		return (FAILURE);
	}
	return (SUCCESS);
}
