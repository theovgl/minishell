#include "minishell.h"

void	ft_exit(t_config *c)
{
	clean_on_success(c);
	printf("exit\n");
	ft_lstclear(&c->env, free);
	exit(0);
}