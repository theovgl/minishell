/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:49:46 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/10 16:12:37 by abiju-du         ###   ########.fr       */
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
