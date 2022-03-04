/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:24:45 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 21:33:13 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd_list(t_list *cmd_list)
{
	t_list	*current;
	int		i;

	current = cmd_list;
	while (current)
	{
		i = 0;
		if (((t_cmd *)current->content)->cmd)
		{
			while (((t_cmd *)current->content)->cmd[i])
				free(((t_cmd *)current->content)->cmd[i++]);
			free(((t_cmd *)current->content)->cmd);
		}
		if (((t_cmd *)current->content)->path)
			free(((t_cmd *)current->content)->path);
		current = current->next;
	}
	ft_lstclear(&cmd_list, free);
}

void	clean_on_success(t_config *c)
{
	clean_cmd_list(c->cmd_list);
	ft_lstclear(&c->tokens, free);
	free(c->command_line);
}

int	clean_exit(t_config *c, int code)
{
	clean_on_success(c);
	if (code == ERR_ADD_TOKEN)
		printf("an error occured while trying to add a new token\n");
	return (code);
}
