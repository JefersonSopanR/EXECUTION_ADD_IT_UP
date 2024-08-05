/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:18:25 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:18:25 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	ft_print_tokens(void)
{
	t_token	*token;

	token = g_global.token;
	while (token)
	{
		printf("TYPE-> %d  DATA-> %s\n", token->type, token->data);
		token = token->next;
	}
}

void	ft_print_ast(t_node *ast, int depth)
{
	int	i;

	i = depth;
	if (!ast)
		return ;
	while (i > 0)
	{
		printf(" ");
		i--;
	}
	printf("NODE_TYPE-> %d  ", ast->type);
	if (ast->redir && (ast->redir->type == T_REDIR_IN || ast->redir->type == T_REDIR_HEREDOC))
		printf("NODE_REDIR-> %s ", ast->redir->file);
	if (ast->data)
		printf("NODE_DATA-> %s ", ast->data);
	if (ast->redir && (ast->redir->type == T_REDIR_OUT || ast->redir->type == T_REDIR_APPEND))
		printf("NODE_REDIR-> %s ", ast->redir->file);
	printf("\n");
	ft_print_ast(ast->left, depth + 1);
	ft_print_ast(ast->right, depth + 1);
}

void	ft_print_error(t_token *token)
{
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	if (!g_global.cur_token)
	{
		while (token && token->next != g_global.cur_token)
			token = token->next;
		if (ft_is_redir(token->type))
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(token->data, 2);
	}
	else if (g_global.cur_token->type == T_O_PARENTHESIS \
		&& g_global.cur_token->next)
	{
		g_global.cur_token = g_global.cur_token->next;
		ft_putstr_fd(g_global.cur_token->data, 2);
	}
	else if (g_global.cur_token->data)
		ft_putstr_fd(g_global.cur_token->data, 2);
	ft_putstr_fd("'\n", 2);
}

void	ft_print_envp(t_envp *envp)
{
	if (!envp)
		return ;
	while (envp)
	{
		printf("Key-> %s  Value-> %s\n", envp->key, envp->value);
		envp = envp->next;
	}
}
