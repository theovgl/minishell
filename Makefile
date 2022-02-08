NAME	= minishell
SRCS	= $(addprefix src/, main.c \
			$(addprefix prompt/, prompt.c) \
			$(addprefix signal/, handle_signal.c)) \
		  $(addprefix lib/get_next_line/, get_next_line.c get_next_line_utils.c)
OBJS	= $(SRCS:.c=.o)
INCL	= -I includes
CC		= clang
CFLAGS	= -Wall -Wextra
LIBS	= -lreadline
RM		= rm -f

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
