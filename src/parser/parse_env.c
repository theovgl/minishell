/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:41:12 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 18:16:11 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Add the final / to the different paths
 *
 * @param c
 */
static void	format_path(t_config *c)
{
	int		i;
	char	*tmp;

	i = 0;
	while (c->path[i])
	{
		tmp = ft_strjoin(c->path[i], "/");
		free(c->path[i]);
		c->path[i] = tmp;
		i++;
	}
}

/**
 * @brief Check if the PATH variable is present in the env
 * If the variable exist the function split all the different paths in a char**
 *
 * @param c
 * @return int
 */
int	parse_env(t_config *c)
{
	char	*ret;

	ret = ft_strdup(getenv("PATH"));
	if (ret == NULL)
		return (FAILURE);
	if (!c->path)
		c->path = ft_split(ret, ':');
	free(ret);
	format_path(c);
	return (SUCCESS);
}
