#include "minishell.h"

// Takes the position 'i' of the command line.
// Put <, <<, > and >> in the chained list. 
// Returns the new position 'i'.
int	ft_islessgreat(t_config *c, int i)
{
	if (c->command_line[i] == '<' && c->command_line[i + 1] != '<')
	{
		if (add_token(c, i, i, LESS) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '<' && c->command_line[i + 1] == '<')
	{
		if (add_token(c, i, i + 1, LLESS) == FAILURE)
			return (-1);
		i += 2;
	}
	if (c->command_line[i] == '>' && c->command_line[i + 1] != '>')
	{
		if (add_token(c, i, i, GREAT) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '>' && c->command_line[i + 1] == '>')
	{
		if (add_token(c, i, i + 1, GGREAT) == FAILURE)
			return (-1);
		i += 2;
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put |, ' and " in the chained list. 
// Returns the new position 'i'.
int	ft_isquote(t_config *c, int i)
{
	int j;

	j = 0;
	if (c->command_line[i] == '\'')
	{
		if (add_token(c, i, i, SQUOTE) == FAILURE)
			return (-1);
		i++;
		while (c->command_line[i + j] != '\'' && c->command_line[i + j])
			j++;
		if (add_token(c, i, j, WORD) == FAILURE)
			return (-1);
		i += j;
	}
	if (c->command_line[i] == '\"')
	{
		if (add_token(c, i, i, DQUOTE) == FAILURE)
			return (-1);
		i++;
		while (c->command_line[i + j] != '\"' && c->command_line[i + j])
			j++;
		if (add_token(c, i, j, WORD) == FAILURE)
			return (-1);
		i++;
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put $ and ? in the chained list. 
// Returns the new position 'i'.
int	ft_isdollar_qmark_pipe(t_config *c, int i)
{
	if (c->command_line[i] == '$')
	{
		if (add_token(c, i, i, DOLLAR) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '?')
	{
		if (add_token(c, i, i, QMARK) == FAILURE)
			return (-1);
		i++;
	}
	if (c->command_line[i] == '|')
	{
		if (add_token(c, i, i, PIPE) == FAILURE)
			return (-1);
		i++;
	}
	return (i);
}

// Takes the position 'i' of the command line.
// Put a word in the chained list.
// If '-' precede the word, the type is set as ARG.
// Returns the new position 'i'.
int	ft_isword(t_config *c, int i)
{
	int	j;

	j = 0;
	while (c->command_line[i + j] && \
	c->command_line[i + j] != '-' && \
	c->command_line[i + j] != '\"' && \
	c->command_line[i + j] != '\'' && \
	c->command_line[i + j] != '?' && \
	c->command_line[i + j] != '$' && \
	c->command_line[i + j] != '<' && \
	c->command_line[i + j] != '>' && \
	c->command_line[i + j] != '|' && \
	c->command_line[i + j] != ' ' && \
	c->command_line[i + j] != '\f' && \
	c->command_line[i + j] != '\n' && \
	c->command_line[i + j] != '\r' && \
	c->command_line[i + j] != '\t' && \
	c->command_line[i + j] != '\v')
		j++;
	if (add_token(c, i, i + j, WORD) == FAILURE)
		return (clean_exit(ERR_ADD_TOKEN));
	return (i + j);
}

// The lexer takes the char* resulting of the readline.
// It suposedly contains the commands that minishell has to execute.
// The lexer set apart every part of the command list and save them as tokens in a linked chain.
int lexer(t_config *c)
{
	int	i;

	i = 0;
	while (c->command_line[i])
	{
printf("c->command_line[%d] == %c\n", i, c->command_line[i]);
		while (c->command_line[i] && \
	c->command_line[i] == '\f' && \
	c->command_line[i] == ' ' && \
	c->command_line[i] == '\n' && \
	c->command_line[i] == '\r' && \
	c->command_line[i] == '\t' && \
	c->command_line[i] == '\v')
		i++;
printf("here\n");
		if (c->command_line[i])
			i = ft_isword(c, i);
printf("here\n");
		if (i == -1)
			return (FAILURE);
printf("here\n");
		if (c->command_line[i])
			i = ft_isquote(c, i);
printf("here\n");
		if (i == -1)
			return (FAILURE);
printf("here\n");
		if (c->command_line[i])
			i = ft_islessgreat(c, i);
printf("here\n");
		if (i == -1)
			return (FAILURE);
printf("here\n");
		if (c->command_line[i])
			i = ft_isdollar_qmark_pipe(c, i);
printf("here\n");
		if (i == -1)
			return (FAILURE);
printf("here\n");
		if (c->command_line[i])
			i++;
	}
	return (SUCCESS);
}

// add_token takes a portion of the command line and a type of token.
// add_token save the portion in the chained list.
// add_token fill c.type accordingly.
int add_token(t_config *c, int start, int end, int type)
{
	int		i;
	char	*content;

	i = 0;
	ft_lstadd_back(&c->first_node, ft_lstnew(c->first_node));
	content = (ft_lstlast(c->first_node))->content;
	content = malloc(sizeof(char) * (end - start + 2));
	if (content == NULL)
		return (FAILURE);
	while (start + i <= end)
	{
		content[i] = c->command_line[start + i];
		i++;
	}
printf("i == %d\n", i);
	content[i] = 0;
	(ft_lstlast(c->first_node))->type = type;
	return (SUCCESS);
}
