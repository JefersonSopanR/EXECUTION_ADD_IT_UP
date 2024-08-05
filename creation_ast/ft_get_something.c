/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_something.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 11:10:45 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 11:10:45 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	*ft_get_node_data(void)
{
	char	*data;

	if (g_global.cur_token->type == T_WORD)
		data = ft_strdup(g_global.cur_token->data);
	else
	{
		data = ft_strdup("");
		return (data);
	}
	g_global.cur_token = g_global.cur_token->next;
	return (data);
}

t_redir	*ft_fill_redir(t_redir **redir)
{
	while (g_global.cur_token && ft_is_redir(g_global.cur_token->type) && !g_global.error_type)
	{
		ft_add_redir_back(redir, ft_new_redir());
	}
	return (*redir);
}

t_node	*ft_get_cmd_node(void)
{
	t_node	*node;
	char	*tmp;
	char	*new_data;

	node = ft_new_node(NODE_CMD);
	if (!node)
		return (NULL);
	node->data = ft_get_node_data();
	while (g_global.cur_token && !g_global.error_type && \
	(g_global.cur_token->type == T_WORD \
	|| ft_is_redir(g_global.cur_token->type)))
	{
		if (g_global.cur_token->type == T_WORD)
		{
			tmp = ft_strjoin(node->data, " ");
			new_data = ft_strjoin(tmp, g_global.cur_token->data);
			free(tmp);
			free(node->data);
			node->data = new_data;
			g_global.cur_token = g_global.cur_token->next;
		}
		else if (ft_is_redir(g_global.cur_token->type))
			node->redir = ft_fill_redir(&node->redir);
	}
	return (node);
}
