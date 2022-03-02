/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:58:41 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/11 12:11:52 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compte le nombre d’éléments de la liste.
 *
 * @param lst
 * @return int
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
