#include "includes/minishell.h"

// The lexer takes the char* resulting of the readline.
// It suposedly contains the commands that minishell has to execute.
// The lexer set apart every part of the command list and save them as tokens in a linked chain.
void lexer(t_config *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (c->command_line[i])
	{
		while (ft_isalnum(c->command_line[i + j]) == 0)
		{
			add_token(c, i, j, WORD);
			j++;
		}
		i += j;
		i++;
	}
}

// add_token takes a portion of the command line and a type of token.
// add_token save the portion in the chained list.
// add_token fill c.type accordingly.
void add_token(t_config *c, int start, int end, int type)