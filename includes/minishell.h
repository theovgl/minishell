/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiju-du <abiju-du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 21:44:27 by tvogel            #+#    #+#             */
/*   Updated: 2022/03/04 19:49:53 by abiju-du         ###   ########.fr       */
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
# include <fcntl.h>

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
	BUILTIN,
	NOT_BUILTIN,
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
	int	in;
	int	out;
}	t_io;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	int		builtin;
	t_io	io;
}	t_cmd;

typedef struct s_config
{
	t_list	*tokens;
	t_list	*env;
	char	**path;
	char	*cmd_path;
	t_list	*cmd_list;
	char	*command_line;
	int		last_return;
}	t_config;

// SIGNAL
void	handle_signal(void);

// SRC
int		clean_exit(int code);

// INIT
int		init(t_config *c, char *ep[]);

// LEXER
int		lexer(t_config *c);
int		add_token(t_config *c, int start, int end, int type);
char	*translator(t_config *c, char *line);

//EXEC
int		exec(t_config *c, char *envp[]);

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
void	*ft_memdup(void *src, int size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// PARSER

int		parser(t_config *c);
int		parse_env(t_config *c);
void	parse_tokens(t_config *c);
int		get_cmd_size(t_list *node);
void	parse_word(t_config *c, t_list *list, t_cmd *to_fill);
void	add_cmd_to_list(t_config *c, t_cmd *cmd);
int		parse_redirect(t_list *list, t_cmd *cmd);
int		is_builtin(char *to_check);

// BUILTINS
int		ft_env(t_config *c, char *ep[]);
int		echo(char *av[]);
int		export(t_config *c, char *s);
int		pwd(void);
void	unset(t_config *c, char *word[]);
int		cd(char *path);

// ENV
void	add_in_env(t_config *c, char *word, char *def);
void	print_env(t_config *c);

// UNSET
void	unset(t_config *c, char *word[]);

#endif
