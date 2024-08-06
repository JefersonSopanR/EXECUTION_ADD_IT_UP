/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:21:20 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:21:20 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redir(t_redir *redir)
{
	t_redir	*next;

	if (!redir)
		return ;
	while (redir)
	{
		free(redir->file);
		next = redir->next;
		free(redir);
		redir = next;
	}
}

void	ft_free_cmd(t_node *ast)
{
	if (ast->data)
		free(ast->data);
	ft_free_redir(ast->redir);
}

void	ft_free_ast(t_node *ast)
{
	if (!ast)
		return ;
	ft_free_cmd(ast);
	ft_free_ast(ast->left);
	ft_free_ast(ast->right);
	free(ast);
}

void	ft_free_envp(t_envp **envp)
{
	t_envp	*cur;
	t_envp	*next;

	if (!*envp)
		return ;
	cur = *envp;
	while (cur)
	{
		free(cur->key);
		free(cur->value);
		next = cur->next;
		free(cur);
		cur = next;
	}
	*envp = NULL;
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
