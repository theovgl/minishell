#include "minishell.h"

int	pwd(void)
{
	char	buff[256];

	if (getcwd(buff, 256) == NULL)
		return (FAILURE);
	printf("%s\n", buff);
	return (SUCCESS);
}
