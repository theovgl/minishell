/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:36:16 by abiju-du          #+#    #+#             */
/*   Updated: 2022/03/01 23:36:42 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	buff[256];

	if (getcwd(buff, 256) == NULL)
		return (FAILURE);
	printf("%s\n", buff);
	return (SUCCESS);
}
