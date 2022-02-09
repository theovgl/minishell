#include "includes/minishell.h"

// Takes the position 'i' of the command line.
// Put <, <<, > and >> in the chained list. 
// Returns the new position 'i'.
int	ft_islessgreat(t_config *c, int i)
{
	if (c->command_line[i] == '<' && c->command_line[i + 1] != '<')
	{
		if (add_token(c, i, i++, LESS) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	if (c->command_line[i] == '<' && c->command_line[i + 1] == '<')
	{
		if (add_token(c, i, ++i, LLESS) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	if (c->command_line[i] == '>' && c->command_line[i + 1] != '>')
	{
		if (add_token(c, i, i++, GREAT) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	if (c->command_line[i] == '>' && c->command_line[i + 1] == '>')
	{
		if (add_token(c, i, ++i, GGREAT) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put |, ' and " in the chained list. 
// Returns the new position 'i'.
int	ft_iscotepipe(t_config *c, int i)
{
	if (c->command_line[i] == '|')
	{
		if (add_token(c, i, i++, PIPE) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	if (c->command_line[i] == '\'')
	{
		if (add_token(c, i, i++, SQUOTE) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	if (c->command_line[i] == '\"')
	{
		if (add_token(c, i, i++, DQUOTE) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put $ and ? in the chained list. 
// Returns the new position 'i'.
int	ft_isdollarqmark(t_config *c, int i)
{
	if (c->command_line[i] == '$')
	{
		if (add_token(c, i, i++, DOLLAR) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	if (c->command_line[i] == '?')
	{
		if (add_token(c, i, i++, QMARK) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put a word in the chained list. 
// Returns the new position 'i'.
int	ft_isword(t_config *c, int i)
{
	int	j;

	j = 0;
	while (ft_isalnum(c->command_line[i + j]) == 0)
	{
		if (add_token(c, i, i + j, WORD) == FAILURE)
			return (clean_exit(ERR_ADD_TOKEN));
		j++;
	}
	return (i + j);
}

// The lexer takes the char* resulting of the readline.
// It suposedly contains the commands that minishell has to execute.
// The lexer set apart every part of the command list and save them as tokens in a linked chain.
void lexer(t_config *c)
{
	int	i;
	int	j;

	i = 0;
	while (c->command_line[i])
	{
		i = ft_isword(c, i);
		i = ft_iscotepipe(c, i);
		i = ft_islessgreat(c, i);
		i = ft_isdollarqmark(c, i);
		i++;
	}
}

// add_token takes a portion of the command line and a type of token.
// add_token save the portion in the chained list.
// add_token fill c.type accordingly.
int add_token(t_config *c, int start, int end, int type)
{

}