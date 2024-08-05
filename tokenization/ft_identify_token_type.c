/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_identify_token_type.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:20:44 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:20:44 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_identify_parenthesis(t_token **token, char *line, int *i)
{
	if (line[*i] == '(')
	{
		ft_add_back(token, ft_new_token(T_O_PARENTHESIS, ft_strdup("(")));
		(*i)++;
	}
	else
	{
		ft_add_back(token, ft_new_token(T_C_PARENTHESIS, ft_strdup(")")));
		(*i)++;
	}
}

void	ft_identify_and_or(t_token **token, char *line, int *i)
{
	if (!ft_strncmp(&line[*i], "&&", 2))
	{
		ft_add_back(token, ft_new_token(T_AND, ft_strdup("&&")));
		(*i) += 2;
	}
	else
	{
		ft_add_back(token, ft_new_token(T_OR, ft_strdup("||")));
		(*i) += 2;
	}
}

void	ft_identify_operators(t_token **token, char *line, int *i)
{
	if (line[*i] == '<' || line[*i] == '>')
		ft_identify_redir(token, line, i);
	else if (line[*i] == '(' || line[*i] == ')')
		ft_identify_parenthesis(token, line, i);
	else if (!ft_strncmp(&line[*i], "&&", 2) || !ft_strncmp(&line[*i], "||", 2))
		ft_identify_and_or(token, line, i);
	else if (line[*i] == '|')
	{
		ft_add_back(token, ft_new_token(T_PIPE, ft_strdup("|")));
		(*i)++;
	}
}
