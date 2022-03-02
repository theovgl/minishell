#include "minishell.h"

int	int_len(int nb)
{
	int	div;
	int	len;

	len = 0;
	div = nb;
	if (nb <= 0)
		len++;
	while (div != 0)
	{
		div /= 10;
		len++;
	}
	return (len);
}

replace_var(t_config *c, int len_diff)
{
	char	*new_command_line;

	new_command_line = malloc(sizeof(char *) * (ft_strlen(c->command_line) + len_diff + 1));

}

int	find_var(t_config *c, int *current_pos)
{
	t_list	*current;
	int		pos;
	int		i;
	int		line_number;

	current = c->env;
	if (!c->command_line[*current_pos])
		return (0);
	line_number = 0;
	while (current)
	{
		i = 0;
		pos = *current_pos;
		while (c->command_line[pos] && ((char *)(current->content))[i] \
		&& c->command_line[pos] == ((char *)(current->content))[i])
		{
			i++;
			pos++;
		}
		if (ft_isspace(c->command_line[pos]) && ((char *)(current->content))[i] == '=')
			return (line_number);
		line_number++;
		current = current->next;
	}
	return (-1);
}

int	diff_calcullator(t_config *c, int *current_pos)
{
	t_list	*current;
	int		pos;
	int		i;
	int		len_word;

	current = c->env;
	if (!c->command_line[*current_pos])
		return (0);
	while (current)
	{
		i = 0;
		pos = *current_pos;
		while (c->command_line[pos] && ((char *)(current->content))[i] \
		&& c->command_line[pos] == ((char *)(current->content))[i])
		{
			i++;
			pos++;
		}
		if (ft_isspace(c->command_line[pos]) && ((char *)(current->content))[i] == '=')
		{
			len_word = pos - *current_pos;
			*current_pos = pos;
			while (((char *)(current->content))[i])
				i++;
			return(i - len_word);
		}
		current = current->next;
	}
	while (!ft_isspace(c->command_line[pos]))
		pos++;
	len_word = pos - *current_pos;
	*current_pos = pos;
	return (-len_word);
}

void	local_translate(t_config *c)
{
	int		i;
	int		len_diff;

	i = 0;
	len_diff = 0;
	while (c->command_line[i])
	{
		if (c->command_line[i] == '\'')
		{
			while (c->command_line[i] && c->command_line[i] != '\'')
				i++;
		}
		if (c->command_line[i] == '$')
		{
			i++;
			if (c->command_line[i] == '?')
				len_diff += int_len(c->last_return) - 2;
			else if (c->command_line[i])
				len_diff += diff_calculator(c, &i);
		}
		else
			i++;
	}
	replace_var(c, len_diff);
}