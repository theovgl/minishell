/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:44:27 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/14 11:39:33 by tvogel           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line.h"

enum {
	SUCCESS = 0,
	FAILURE,
	WORD,
	GREAT,
	GGREAT,
	LESS,
	LLESS,
	PIPE,
	SQUOTE,
	DQUOTE,
	DOLLAR,
	QMARK,
	ERR_ADD_TOKEN,
	ERR_INIT,
	ERR_MALLOC,
	ERR_LEXER
};

typedef struct s_list	t_list;

struct s_list
{
	void	*content;
	int		type;
	t_list	*next;
	t_list	*prev;
};

typedef struct s_config
{
	char	*command_line;
	t_list	*first_node;

}	t_config;

// SIGNAL
void	handle_signal(void);

// SRC
int		clean_exit(int code);

// INIT
int		init(t_config *c);

// LEXER
int		lexer(t_config *c);
int		add_token(t_config *c, int start, int end, int type);

// UTILS
int		ft_isalnum(int c);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));
int		ft_lstsize(t_list *lst);
int		ft_isspace(const char c);

#endif
