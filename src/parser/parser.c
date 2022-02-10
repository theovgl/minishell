/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:35:46 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/10 17:51:08 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_config *c)
{
	c->tokens.prev = NULL;
	c->tokens.type = WORD;
	c->tokens.content = "ls";
	c->tokens.next = ft_lstnew("-l");
	c->tokens.next->type = WORD;
	c->tokens.next->next = ft_lstnew("|");
	c->tokens.next->next->type = PIPE;
	c->tokens.next->next->next = ft_lstnew("cat");
	c->tokens.next->next->next->type = WORD;
	c->tokens.next->next->next->next = NULL;
}

/**
 * @brief Add the final / to the different paths
 *
 * @param c
 */
void	format_path(t_config *c)
{
	int	i;

	i = 0;
	while (c->env[i])
	{
		c->env[i] = ft_strjoin(c->env[i], "/");
		i++;
	}
}

/**
 * @brief Check if the function exist in the env
 *
 * @param c
 * @param cmd
 * @return int
 */
int	check_path(t_config *c, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (c->env[i] && cmd != NULL)
	{
		temp = ft_strjoin(c->env[i], cmd);
		if (access(temp, F_OK) == 0)
		{
			c->cmd_path = ft_strdup(temp);
			free(temp);
			printf("%s\n", c->cmd_path);
			return (1);
		}
		free(temp);
		i++;
	}
	if (cmd == NULL)
		c->cmd_path = ft_strdup(cmd);
	else
		c->cmd_path = NULL;
	return (0);
}

void	parse_word(t_config *c)
{
	// t_list	*current;

	// current = list;
	// while (current)
	// {
	// 	/* code */
	// }

}

void	parse_tokens(t_config *c)
{
	t_list	*current;
	t_list	*new_cmd;
	t_cmd	cmd;

	current = &c->tokens;
	cmd.cmd = NULL;
	while (current)
	{
		while (current && current->type == WORD)
		{
			if (cmd.cmd == NULL)
				cmd.cmd = ft_strdup(current->content);
			else
			{
				cmd.cmd = ft_strjoin(cmd.cmd, " ");
				cmd.cmd = ft_strjoin(cmd.cmd, current->content);
			}
			current = current->next;
		}
		if (current && current->next != NULL)
			current = current->next;
	}
	new_cmd = ft_lstnew(&cmd);
	printf("%s\n", cmd.cmd);
}

int	parser(t_config *c)
{
	int	i;

	i = 0;
	init_list(c);
	if (parse_env(c))
	{
		printf("PATH not found\n");
		return (1);
	}
	parse_tokens(c);
	// check_path(c, c->tokens.content);
	return (0);
}
