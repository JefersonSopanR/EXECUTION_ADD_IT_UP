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
