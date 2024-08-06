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