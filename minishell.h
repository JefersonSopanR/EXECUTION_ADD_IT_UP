/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesopan- <jesopan-@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-31 10:18:08 by jesopan-          #+#    #+#             */
/*   Updated: 2024-07-31 10:18:08 by jesopan-         ###   ########ç         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

typedef enum e_type
{
	T_WORD,
	T_O_PARENTHESIS,
	T_C_PARENTHESIS,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_PIPE,
	T_AND,
	T_OR,
}	t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_OR,
	NODE_AND,
}	t_node_type;

typedef enum e_rror
{
	E_NONE,
	E_SYNTAX,
}	t_error;

typedef struct s_node
{
	t_node_type		type;
	t_redir			*redir;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_global
{
	t_token		*cur_token;
	t_error		error_type;
	t_token		*token;
	t_node		*ast;
	t_envp		*envp;
	bool		quote;
	char		**dup_envp;
	int			stdin;
	int			stdout;
}	t_global;

//init

void	ft_init_minishell(void);
void	ft_reset_fd(void);

//TOKENIZATION

void	ft_free_tokens(t_token **token);
t_token	*ft_get_tokens(char *line);
t_token		*ft_new_token(t_token_type type, char *data);
void		ft_add_back(t_token **token, t_token *new);
void		ft_free_tokens(t_token **token);
bool		ft_check_quotes(char *line);
void		ft_print_tokens(void);
void		ft_id_redir_input(t_token **token, char *line, int *i);
void		ft_id_redir_output(t_token **token, char *line, int *i);
void		ft_identify_redir(t_token **token, char *line, int *i);
void		ft_identify_parenthesis(t_token **token, char *line, int *i);
void		ft_identify_and_or(t_token **token, char *line, int *i);
void		ft_identify_operators(t_token **token, char *line, int *i);
int			ft_keep_in_quotes(char *line, int *i, char *quote, bool flag);
char		*ft_append_quoted_word(char *line, int *i, char quote, char *data);
char		*ft_join_normal_data(char *line, int *i, char *data, char *quote);

void	ft_prep_quote_word(t_token **token, char *line, int *i, char *data);


//PARSING

t_node		*ft_new_node(t_node_type type);
t_redir		*ft_new_redir(void);
void		ft_add_redir_back(t_redir **redir, t_redir *new);
char		*ft_get_node_data(void);
bool		ft_is_not_op(char *line, int *i);
bool		ft_is_cmd(t_token *token);
bool		ft_is_redir(t_token_type type);
t_redir		*ft_fill_redir(t_redir **redir);
t_node		*ft_get_cmd_node(void);
t_node		*ft_primary(void);
t_node		*ft_expression(int min_prec);
t_node		*ft_create_ast(t_token *token);
void		ft_free_redir(t_redir *redir);
void		ft_free_cmd(t_node *ast);
void		ft_free_ast(t_node *ast);
t_node		*ft_connect_nodes(t_token_type op, t_node *left, t_node *right);
t_node_type	ft_convert_type(t_token_type op);
int			ft_prec(t_token_type type);
t_node		*ft_new_node(t_node_type type);
bool		ft_is_cmd(t_token *token);


//EXECUTION

void	free_split(char **split);
char	*create_path(char *path, char *cmd);
char	*get_path(char *cmd, char **envp);
void	execute_command(char *command, char **envp);
int	get_here_doc(char *delimeter);
void	child_get_input(char *delimeter, int pfd[]);
int	ft_redir_append(char	*file);
int	ft_redir_out(char	*file);
int	ft_redir_in(char	*file);
void	ft_execute_command(t_node *node);
int	ft_execute_normal_cmd(t_node *node);
int	ft_check_redirections(t_redir	*redirect);
void	ft_child_process(t_node *node, char **envp);
void	ft_start_execution(t_node *ast);
void	ft_reset_fd(void);


//PRINTERS
void		ft_print_ast(t_node *ast, int depth);
void		ft_print_error(t_token *token);


//ENVP
t_envp		*ft_duplicate_envp(char **env);
void		ft_add_back_envp(t_envp **envp, t_envp *new);
t_envp		*ft_new_envp(char *key, char *value);
void		ft_free_envp(t_envp **envp);
void		ft_print_envp(t_envp *envp);
char		*ft_get_value(char *env);
char		*ft_get_key(char *env);

#endif