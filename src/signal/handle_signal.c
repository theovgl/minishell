/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 19:13:47 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/09 18:30:13 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Write \n then replace the line with a new prompt
*/
static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (g_pid == 0)
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
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
