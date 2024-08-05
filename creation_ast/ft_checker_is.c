/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_is.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:30:34 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:30:34 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

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

bool	ft_is_not_op(char *line, int *i)
{
	if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|' || \
	line[*i] == ' ' || line[*i] == '\t' || line[*i] == '(' || \
	line[*i] == ')' || !ft_strncmp(&line[*i], "&&", 2))
		return (true);
	return (false);
}

bool	ft_is_cmd(t_token *token)
{
	if (token->type == T_PIPE || token->type == T_OR || token->type == T_AND)
		return (false);
	return (true);
}

bool	ft_is_redir(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_REDIR_APPEND \
	|| type == T_REDIR_HEREDOC)
		return (true);
	return (false);
}
