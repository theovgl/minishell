NAME	= minishell
SRCS	= main.c \
			handle_signal.c \
			ft_lstnew.c ft_lstsize.c ft_lstmap.c ft_lstlast.c ft_lstiter.c ft_lstdelone.c ft_lstclear.c ft_lstadd_front.c ft_lstadd_back.c \
			get_next_line.c get_next_line_utils.c
OBJS	= $(SRCS:.c=.o)
INCL	= -I includes
CC		= clang
CFLAGS	= -Wall -Wextra
LIBS	= -lreadline
RM		= rm -f

vpath %.c src/ src/utils/ src/signal/ lib/get_next_line

%.o:	%.c
		$(CC) $(CFLAGS) $(INCL) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
