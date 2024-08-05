/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicate_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:21:38 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:21:38 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	*ft_get_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (env[i])
	{
		if (!ft_strncmp(&env[i], "=", 1))
			break ;
		i++;
	}
	key = ft_substr(env, 0, i);
	return (key);
}

char	*ft_get_value(char *env)
{
	int		start;
	char	*value;
	int		i;

	i = 0;
	start = 0;
	value = NULL;
	while (env[i] && env[i] != '=')
		i++;
	start = i;
	while (env[i])
		i++;
	value = ft_substr(env, start, i - start);
	return (value);
}

t_envp	*ft_new_envp(char *key, char *value)
{
	t_envp	*envp;

	envp = (t_envp *)ft_calloc(1, sizeof(t_envp));
	if (!envp)
		return (NULL);
	envp->key = key;
	envp->value = value;
	return (envp);
}

void	ft_add_back_envp(t_envp **envp, t_envp *new)
{
	t_envp	*cur;

	if (!*envp)
	{
		*envp = new;
		return ;
	}
	cur = *envp;
	while (cur && cur->next)
		cur = cur->next;
	cur->next = new;
}

t_envp	*ft_duplicate_envp(char **env)
{
	t_envp	*envp;
	int		i;
	char	*key;
	char	*value;

	g_global.dup_envp = env;
	i = 0;
	envp = NULL;
	while (env[i])
	{
		key = ft_get_key(env[i]);
		value = ft_get_value(env[i]);
		ft_add_back_envp(&envp, ft_new_envp(key, value));
		i++;
	}
	return (envp);
}
