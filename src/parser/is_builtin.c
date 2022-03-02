/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:46:23 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/02 15:40:25 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *to_check)
{
	if (!to_check)
		return (0);
	if (ft_strncmp("echo", to_check, 4) == 0
		|| ft_strncmp("cd", to_check, 2) == 0
		|| ft_strncmp("pwd", to_check, 3) == 0
		|| ft_strncmp("export", to_check, 6) == 0
		|| ft_strncmp("unset", to_check, 5) == 0
		|| ft_strncmp("env", to_check, 3) == 0
		|| ft_strncmp("exit", to_check, 4) == 0)
	{
		return (1);
	}
	return (0);
}
