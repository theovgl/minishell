/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:13:47 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/18 17:13:42 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Write \n then replace the line with a new prompt
*/
void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	g_global.ret = 130;
	if (g_global.child == 0)
	{
		rl_on_new_line();
		rl_replace_line("", sig);
		rl_redisplay();
	}
}

/**
 * This function is used to handle signals like ctrl-c and ctrl-\
*/
void	handle_signal(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("Signal");
		exit(g_global.ret);
	}
	if (signal(SIGINT, &handle_sigint) == SIG_ERR)
	{
		perror("Signal");
		exit(g_global.ret);
	}
}
