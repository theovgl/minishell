#include "../../includes/minishell.h"

int find_eq(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	s[i] = 0;
	return (-1);
}

char	*get_word(char *s, char *word, int i)
{
	int j;

	j = 0;
	word = malloc(sizeof(char *) * i + 1);
	if (!word)
		return (NULL);
	while (j < i)
	{
		word[j] = s[j];
		j++;
	}
	word[i] = 0;
	return (word);
}

char	*get_def(char *s, char *def, int i)
{
	int j;

	j = i;
	while (s[j])
		j++;
	def = malloc(sizeof(char *) * j - i + 1);
	if (!def)
		return (NULL);
	j = 0;
	while (s[i])
	{
		def[j] = s[i];
		i++;
		j++;
	}
	def[i] = 0;
	return (def);
}

int	export(char *s)
{
	int		i;
	char	*word;
	char	*def;

	word = NULL;
	def = NULL;
	i = find_eq(s);
	if (i == -1)
		return (FAILURE);
	word = get_word(s, word, i);
	if (!word)
		return (FAILURE);
	def = get_def(s, def, i + 1);
printf("word == %s\ndef == %s\n", word, def);
	return (SUCCESS);
}

int main()
{
	char *s = "TEST=ok!";
	export(s);
}