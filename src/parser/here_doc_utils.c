/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:41:14 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/19 16:42:37 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_fd_manager(t_cmd *cmd, int fd[2])
{
	if (cmd->io.in != STDIN_FILENO)
	{
		dup2(fd[0], cmd->io.in);
		close(fd[0]);
	}
	else
		cmd->io.in = fd[0];
}
