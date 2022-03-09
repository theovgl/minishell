/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 15:11:30 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/09 12:04:36 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	char	*s;
	int		i;

	i = 0;
	s = (char *)src;
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
	{
		return (NULL);
	}
	while (src && src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
