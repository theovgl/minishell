#include "minishell.h"

int	clean_exit(int code)
{
	if (code == ERR_ADD_TOKEN)
		printf("an error occured while trying to add a new token\n");
	return (code);
}