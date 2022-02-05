/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:08:15 by tvogel            #+#    #+#             */
/*   Updated: 2021/05/20 13:50:18 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *str)
{
	unsigned int	i;
	unsigned int	n;
	char			*ret;

	i = 0;
	n = 0;
	while (str[i] && str[i] != '\n')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	while (n < i && str[n])
	{
		ret[n] = str[n];
		n++;
	}
	ret[n] = 0;
	return (ret);
}

char	*next_line(char *s)
{
	int		i;
	int		n;
	int		l;
	char	*dest;

	i = 0;
	l = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	n = ft_strlen(s) - i + 1;
	dest = malloc(sizeof(char) * n);
	if (!dest)
		return (NULL);
	i++;
	while (s[i])
		dest[l++] = s[i++];
	dest[l] = 0;
	free(s);
	return (dest);
}

int	get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	static char		*nl;
	int				ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	ret = 1;
	while (isendline(nl) == -1 && ret != 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
			return (-1);
		buff[ret] = '\0';
		nl = ft_join(nl, buff);
	}
	*line = get_line(nl);
	nl = next_line(nl);
	if (ret == 0)
		return (0);
	return (1);
}
