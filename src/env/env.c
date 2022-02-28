/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:16:12 by abiju-du          #+#    #+#             */
/*   Updated: 2022/02/28 21:41:33 by abiju-du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_config *c, char *ep[])
{
	int		i;
	t_list	*tmp;		

	if (!ep[i])
		return (FAILURE);
	i = 0;
	while (ep[i])
	{
		tmp = malloc(sizeof(t_list));
		tmp->content = ft_strdup(ep[i]);
		ft_lstadd_back(&c->env, tmp);
		i++;
	}
	return (SUCCESS);
}

// int main(int ac, char *av[], char *ev[])
// {
// 	t_config	c;
// 	t_list		*current;

// 	ft_env(&c, ev);
// 	current = c.env;
// 	while (ac && av && ev)
// 	{
// 		printf("%s\n", (char *)(current->content));
// 		current = current->next;
// 		if (current == NULL)
// 			ac = 0;
// 	}
// }