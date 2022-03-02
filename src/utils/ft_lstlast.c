/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:29:40 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/11 12:12:07 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Renvoie le dernier élément de la liste.
 *
 * @param lst
 * @return t_list*
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}
