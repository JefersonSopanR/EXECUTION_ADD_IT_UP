/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:33:21 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:33:21 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_prec(t_token_type type)
{
	if (type == T_AND || type == T_OR)
		return (0);
	else if (type == T_PIPE)
		return (1);
	return (0);
}

t_node_type	ft_convert_type(t_token_type op)
{
	if (op == T_PIPE)
		return (NODE_PIPE);
	else if (op == T_AND)
		return (NODE_AND);
	return (NODE_OR);
}

t_node	*ft_connect_nodes(t_token_type op, t_node *left, t_node *right)
{
	char	*data;
	t_node	*node;

	data = NULL;
	if (op == T_AND)
		data = ft_strdup("&&");
	else if (op == T_OR)
		data = ft_strdup("||");
	else if (op == T_PIPE)
		data = ft_strdup("|");
	node = ft_new_node(ft_convert_type(op));
	node->data = data;
	node->left = left;
	node->right = right;
	return (node);
}
