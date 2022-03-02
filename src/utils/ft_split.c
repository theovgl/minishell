/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:22:46 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/09 16:59:04 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *str, char c)
{
	int	i;
	int	n;
	int	word;

	word = 0;
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c)
			n = 0;
		else if (n == 0)
		{
			n = 1;
			word++;
		}
		i++;
	}
	return (word);
}

int	count_char(char *s, char c, int position)
{
	int	word_lenght;

	word_lenght = 0;
	while (s[position] != '\0' && s[position] != c)
	{
		word_lenght++;
		position++;
	}
	return (word_lenght);
}

char	**free_error(char **dest, int position)
{
	while (position >= 0)
	{
		free(dest[position]);
		position--;
	}
	free(dest);
	return (NULL);
}

char	**cpy_word(char *str, char c, char **dest, int length)
{
	int	i;
	int	x;
	int	n;

	i = 0;
	x = 0;
	while (str[i] && x < length)
	{
		n = 0;
		while (str[i] == c)
			i++;
		dest[x] = malloc(sizeof(char) * count_char(str, c, i) + 1);
		if (!dest[x])
			return (free_error(dest, x));
		while (str[i] != c && str[i])
		{
			dest[x][n] = str[i];
			n++;
			i++;
		}
		dest[x][n] = '\0';
		x++;
	}
	dest[x] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**dest;
	int		nb_words;

	if (!s)
		return (NULL);
	str = (char *)s;
	nb_words = count_words(str, c);
	dest = malloc(sizeof(char *) * (nb_words + 1));
	if (!dest)
		return (NULL);
	dest = cpy_word(str, c, dest, nb_words);
	return (dest);
}
