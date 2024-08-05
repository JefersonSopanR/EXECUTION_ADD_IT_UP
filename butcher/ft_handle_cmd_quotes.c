#include "minishell.h"

char	**ft_handle_squotes(char *command)
{
	char	**split_command;
	int		i;
	int		j;
	int		start;

	start = 0;
	j = 0;
	i = 0;
	split_command = (char **)ft_calloc(3, sizeof(char *));
	if (!split_command)
		return (NULL);
	while (command[i] != ' ')
		i++;
	split_command[j] = ft_substr(command, 0, i);
	start = ++i;
	i++;
	while (command[i] != '\'')
		i++;
	split_command[++j] = ft_substr(command, start + 1, i - start - 1);
	return (split_command);
}

char	**ft_handle_dquotes(char *command, int quotes, int i, int j)
{
	char	**split_cmd;

	split_cmd = (char **)ft_calloc(quotes + 2, sizeof(char *));
	if (!split_cmd)
		return (NULL);
	while (command[i] && command[i] != ' ')
		i++;
	split_cmd[j++] = ft_substr(command, 0, i);
	while (command[i++])
	{
		if (command[i] == ' ' || command[i] == '\'')
			continue ;
		else
		{
			quotes = i;
			while (command[i++] != '\'' && command[i])
			{
				if (command[i] == '\'')
					split_cmd[j++] = ft_substr(command, quotes, i - quotes);
			}
		}
	}
	return (split_cmd);
}

char	**ft_handle_quotes(char	*command)
{
	char	**split_cmd;
	int		quotes;
	int		i;
	int		j;

	j = 0;
	split_cmd = NULL;
	i = 0;
	quotes = 0;
	while (command[i++])
	{
		if (command[i] == '\'')
			quotes++;
	}
	if (quotes == 2)
		split_cmd = ft_handle_squotes(command);
	else
	{
		i = 0;
		quotes /= 2;
		split_cmd = ft_handle_dquotes(command, quotes, i, j);
	}
	return (split_cmd);
}

