/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:19:02 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/07 13:47:59 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Ajoute l’élément ’new’ à la fin de la liste.
 *
 * @param alst
 * @param new
 */
void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (alst == NULL || new == NULL)
		return ;
	temp = *alst;
	if (temp == NULL)
		*alst = new;
	else
	{
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
		new->prev = temp;
	}
}
