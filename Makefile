NAME	= minishell
SRCS	= main.c \
			handle_signal.c \
			ft_lstnew.c ft_lstsize.c ft_lstmap.c ft_lstlast.c ft_lstiter.c ft_lstdelone.c ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c ft_isspace.c\
			ft_memdup.c ft_memcpy.c ft_strncmp.c\
			get_next_line.c get_next_line_utils.c parser.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c \
			clean_exit.c init.c \
			lexer.c token.c \
			parse_env.c parse_tokens.c \
			exec.c
OBJS	= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
OBJSDIR	= objs
INCL	= -I includes
CC		= clang
CFLAGS	= -Wall -Wextra -g3 -fsanitize=address
LIBS	= -lreadline
RM		= rm -f

vpath %.c src/ src/utils/ src/signal/ lib/get_next_line src/parser/ src/lexer src/exec

$(OBJSDIR)/%.o:	%.c
		$(CC) $(CFLAGS) $(INCL) -c $< -o $@

all:	$(NAME)

$(OBJS): | $(OBJSDIR)

$(OBJSDIR):
		mkdir $(OBJSDIR)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
		$(RM) $(OBJS)
		rm -rf $(OBJSDIR)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
