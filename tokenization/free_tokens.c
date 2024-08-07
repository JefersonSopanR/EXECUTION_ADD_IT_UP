#include "minishell.h"

void	ft_free_tokens(t_token **token)
{
	t_token	*cur;
	t_token	*next;

	cur = *token;
	while (cur)
	{
		free(cur->data);
		next = cur->next;
		free(cur);
		cur = next;
	}
	*token = NULL;
}

bool	ft_check_quotes(char *line)
{
	bool	s_quote;
	bool	d_quote;
	int		i;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (line[i])
	{
		if (line[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (line[i] == '"' && !s_quote)
			d_quote = !d_quote;
		i++;
	}
	if (s_quote || d_quote)
	{
		if (s_quote)
			ft_putstr_fd("Error single quote\n", 2);
		else if (d_quote)
			ft_putstr_fd("Error in double quote\n", 2);
		return (true);
	}
	return (false);
}
