/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:25:19 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:25:19 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

t_node	*ft_primary(void)
{
	t_node	*node;

	node = NULL;
	if (!g_global.cur_token || !ft_is_cmd(g_global.cur_token))
	{
		g_global.error_type = E_SYNTAX;
		return (NULL);
	}
	else if (g_global.cur_token && g_global.cur_token->type == T_O_PARENTHESIS)
	{
		g_global.cur_token = g_global.cur_token->next;
		if (!g_global.cur_token)
			return (g_global.error_type = E_SYNTAX, node);
		node = ft_expression(0);
		if (!g_global.cur_token || g_global.cur_token->type != T_C_PARENTHESIS)
			g_global.error_type = E_SYNTAX;
		else
			g_global.cur_token = g_global.cur_token->next;
		return (node);
	}
	else if (g_global.cur_token && (g_global.cur_token->type == T_WORD \
		|| ft_is_redir(g_global.cur_token->type)))
		return (ft_get_cmd_node());
	return (node);
}

t_node	*ft_expression(int min_prec)
{
	t_node			*left;
	t_node			*right;
	int				next_prec;
	t_token_type	op;

	left = ft_primary();
	if (!left)
		return (NULL);
	while (g_global.cur_token && !ft_is_cmd(g_global.cur_token) && \
		ft_prec(g_global.cur_token->type) >= min_prec && !g_global.error_type)
	{
		op = g_global.cur_token->type;
		g_global.cur_token = g_global.cur_token->next;
		if (!g_global.cur_token || !ft_is_cmd(g_global.cur_token))
			return (g_global.error_type = E_SYNTAX, left);
		next_prec = ft_prec(g_global.cur_token->type) + 1;
		right = ft_expression(next_prec);
		if (!right)
			return (left);
		left = ft_connect_nodes(op, left, right);
	}
	return (left);
}

t_node	*ft_create_ast(t_token *token)
{
	t_node	*ast;

	g_global.cur_token = token;
	ast = ft_expression(0);
	if (g_global.cur_token)
	{
		g_global.error_type = E_SYNTAX;
		return (ast);
	}
	return (ast);
}
