#include "minishell.h"

t_token	*ft_new_token(t_token_type type, char *data)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = data;
	token->type = type;
	return (token);
}

void	ft_add_back(t_token **token, t_token *new)
{
	t_token	*cur;

	if (!*token)
	{
		(*token) = new;
		return ;
	}
	cur = *token;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new;
}