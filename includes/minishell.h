/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvogel <tvogel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:44:27 by tvogel            #+#    #+#             */
/*   Updated: 2022/02/24 16:17:36 by tvogel           ###   ########.fr       */
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

typedef struct s_io
{
	int		i_fd;
	int		o_fd;
}	t_io;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	t_io	io;
}	t_cmd;

typedef struct s_config
{
	t_list	*tokens;
	char	**env;
	char	*cmd_path;
	t_list	*cmd_list;
	char	*command_line;
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
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *src);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_isspace(const char c);

// PARSER

int		parser(t_config *c);
int		parse_env(t_config *c);
void	parse_tokens(t_config *c);

#endif
