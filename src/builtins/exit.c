#include "minishell.h"

void	ft_exit(t_config *c, t_cmd *cmd)
{
	int	exit_status;

	if (cmd->cmd[1])
		exit_status = ft_atoi(cmd->cmd[1]);
	else
		exit_status = -1;
	clean_on_success(c);
	printf("exit\n");
	ft_lstclear(&c->env, free);
	if (exit_status != -1)
		exit(exit_status);
	exit(0);
}
