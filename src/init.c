#include "minishell.h"

int	init(t_config *c)
{
	c->command_line = NULL;
	c->first_node = NULL;
	return (SUCCESS);
}
