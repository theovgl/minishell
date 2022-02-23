#include "minishell.h"

int	cd(char *path)
{
	if (chdir(path) == -1)
		return (FAILURE);
	return (SUCCESS);
}
