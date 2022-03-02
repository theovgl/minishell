/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:44:02 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/11 12:11:31 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Ajoute l’élément ’new’ au début de la liste.
 *
 * @param alst
 * @param new
 */
void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}
