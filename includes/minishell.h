/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:44:27 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/05 22:54:02 by tvogel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <get_next_line.h>

enum {
		WORD = 1,
		GREAT,
		GGREAT,
		LESS,
		LLESS,
		PIPE,
		ARG
};

typedef struct s_list
{
	void	*data;
	int		type;
	t_list	*next;
	t_list	*prev;
}	t_list;


typedef struct	s_config
{
	char	*command_line;
	
}	t_config;

// LEXER
void lexer(t_config *c);

// UTILS
int	ft_isalnum(int c);




#endif
