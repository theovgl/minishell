/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:08:10 by tvogel            #+#    #+#             */
/*   Updated: 2021/05/20 14:01:00 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	isendline(char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (-1);
	while (src[i])
	{
		if (src[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_strlen(const char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		i++;
	}
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n > 0)
		{
			((char *)dest)[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_join(char *s1, char *s2)
{
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	ft_memmove(dest, s1, ft_strlen(s1));
	ft_memmove(dest + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	dest[ft_strlen(s2) + ft_strlen(s1)] = 0;
	free(s1);
	return (dest);
}
