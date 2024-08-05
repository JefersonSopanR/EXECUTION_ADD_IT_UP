/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:13:04 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:13:04 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	*ft_append_quoted_word(char *line, int *i, char quote, char *data)
{
	char	*join;
	char	*tmp;
	int		j;

	j = (*i);
	while (line[*i] && g_global.quote)
	{
		if (line[*i] == quote)
		{
			tmp = ft_substr(line, j, (*i) - j);
			join = ft_strjoin(data, tmp);
			free(tmp);
			free(data);
			data = join;
			if (!ft_keep_in_quotes(line, i, &quote, false))
				return (data);
			if (ft_keep_in_quotes(line, i, &quote, false) == 1)
				data = ft_join_normal_data(line, i, data, &quote);
			(*i) += ft_keep_in_quotes(line, i, &quote, true);
			j = (*i);
		}
		else
			(*i)++;
	}
	return (g_global.quote = true, data);
}

char	*ft_join_normal_data(char *line, int *i, char *data, char *quote)
{
	char	*tmp;
	char	*join;
	int		start;

	(*i)++;
	start = (*i);
	while (line[*i] && !ft_is_not_op(line, i) && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	if (ft_is_not_op(line, i))
		g_global.quote = false;
	else if (line[*i] == '\'' || line[*i] == '"')
		*quote = line[*i];
	tmp = ft_substr(line, start, (*i) - start);
	join = ft_strjoin(data, tmp);
	free(tmp);
	free(data);
	data = join;
	return(data);
}

int	ft_keep_in_quotes(char *line, int *i, char *quote, bool flag)
{
	if (line[*i] == *quote)
	{
		if (line[*i + 1] == '\0' || line[*i + 1] == ' ' || line[*i + 1] == '\t' || line[*i + 1] == '<' || line[*i + 1] == '>' || 
			line[*i + 1] == '|' || !ft_strncmp(&line[*i + 1], "&&", 2) || line[*i + 1] == ')' || line[*i + 1] == '(')
		{
			(*i)++;
			return (0);
		}
		else if (line[*i + 1] != '\'' || line[*i + 1] != '"')
			return (1);
		else if (flag && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
		{
			*quote = line[*i + 1];
			return (2);
		}
	}
	return (0);
}

void	ft_strcpy_data(char *data, char *data_1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] != '\'' && data[i] != '"')
			data_1[j++] = data[i++];
		else
			i++;
	}
	data_1[j] = '\0';
}

void	ft_ignore_quotes(t_token **token, char	*data, int j)
{
	char	*data_1;

	data_1 = (char *)malloc(ft_strlen(data) - j + 1);
	if (!data_1)
		return ;
	ft_strcpy_data(data, data_1);
	free(data);
	ft_add_back(token, ft_new_token(T_WORD, data_1));
}

void	ft_append_word(t_token **token, char *line, int *i)
{
	int		start;
	char	*data;
	int		j;
	char	quote;

	j = 0;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		data = ft_strdup("");
		quote = line[*i];
		(*i)++;
		data = ft_append_quoted_word(line, i, quote, data);
		ft_add_back(token, ft_new_token(T_WORD, data));
		return ;
	}
	start = (*i);
	while (line[*i] && !ft_is_not_op(line, i))
	{
		(*i)++;
		if (line[*i] == '\'' || line[*i] == '"')
			j++;
	}
	data = ft_substr(line, start, (*i) - start);
	if (j > 0)
		ft_ignore_quotes(token, data, j);
	else
		ft_add_back(token, ft_new_token(T_WORD, data));
}

t_token	*ft_procces_line(char *line)
{
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '>' || line[i] == '<' || line[i] == '(' || \
		line[i] == ')' || line[i] == '|' || !ft_strncmp(&line[i], "&&", 2))
			ft_identify_operators(&token, line, &i);
		else
			ft_append_word(&token, line, &i);
	}
	return (token);
}

t_token	*ft_get_tokens(char *line)
{
	t_token	*token;

	if (ft_check_quotes(line))
	{
		free(line);
		return (NULL);
	}
	token = ft_procces_line(line);
	free(line);
	return (token);
}
