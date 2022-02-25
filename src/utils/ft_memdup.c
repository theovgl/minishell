/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 08:42:43 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/25 12:46:35 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memdup(void *src, int size)
{
	char	*destchar;

	destchar = malloc(size);
	destchar = ft_memcpy(destchar, src, size);
	return (destchar);
}
