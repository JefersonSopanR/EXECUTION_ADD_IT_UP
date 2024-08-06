#include "minishell.h"

extern t_global	g_global;

void	ft_start_execution(t_node *ast)
{
	if (!ast)
		return ;
	else if (ast->type == NODE_AND)
	{
		ft_start_execution(ast->left);
		ft_start_execution(ast->right);
	}
	else
	{
		ft_execute_command(ast);
	}
	return ;
}

void	ft_child_process(t_node *node, char **envp)
{
	if (ft_check_redirections(node->redir))
	{
		exit(EXIT_FAILURE);
	}
	execute_command(node->data, envp);
}

int	ft_check_redirections(t_redir	*redirect)
{
	int	i;

	i = 0;
	while (redirect)
	{
		if (redirect->type == T_REDIR_IN)
			i = (ft_redir_in(redirect->file));
		else if (redirect->type == T_REDIR_OUT)
			i = (ft_redir_out(redirect->file));
		else if (redirect->type == T_REDIR_APPEND)
			i = (ft_redir_append(redirect->file));
		else if (redirect->type == T_REDIR_HEREDOC)
			i = (get_here_doc(redirect->file));
		redirect = redirect->next;

	}
	return (i);
}

int	ft_execute_normal_cmd(t_node *node)
{
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Error when forking");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_child_process(node, g_global.dup_envp);
	else
	{
		wait(&exit_status);
		return (0);
	}
	return (0);
}

void	ft_execute_command(t_node *node)
{
	if (node->data[0] == '\0')
	{
		printf("%d\n", g_global.stdin);
		ft_check_redirections(node->redir);
		ft_reset_fd();
		return ;
	}
	else if (ft_execute_normal_cmd(node))
	{
		ft_free_ast(g_global.ast);
		ft_free_tokens(&g_global.token);
		ft_free_envp(&g_global.envp);
	}
	return ;
}

void	ft_reset_fd(void)
{
	int	fd_in;
	int	fd_out;

	fd_in = g_global.stdin;
	fd_out = g_global.stdout;
	dup2(fd_in, 0);
    dup2(fd_out, 1);
    close(fd_in);
    close(fd_out);
}

