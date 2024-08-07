#include "minishell.h"

t_global	g_global;

void	ft_init_minishell(void)
{
	g_global.cur_token = NULL;
	g_global.error_type = E_NONE;
	g_global.token = NULL;
	g_global.ast = NULL;
	g_global.envp = NULL;
	g_global.quote = true;
	g_global.dup_envp = NULL;
	g_global.line = NULL;
}

void	ft_get_minishell_ready(void)
{
	g_global.stdin = dup(0);
	g_global.stdout = dup(STDOUT_FILENO);
}

int	ft_readline(void)
{
	ft_get_minishell_ready();
	g_global.line = readline("My_minishell-> ");
	if (!g_global.line)
		return (1);
	if (!ft_strlen(g_global.line))
	{
		free(g_global.line);
		return (1);
	}
	if (g_global.line[0])
		add_history(g_global.line);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_init_minishell();
	g_global.envp = ft_duplicate_envp(env);
	while (1)
	{
		if (ft_readline())
			continue ;
		if (!ft_strncmp(g_global.line, "exit", 4))
		{
			free(g_global.line);
			break ;
		}
		if (!ft_strncmp(g_global.line, "env", 3))
			ft_print_envp(g_global.envp);
		g_global.token = ft_get_tokens(g_global.line);
		if (!g_global.token)
			continue ;
		ft_print_tokens();
		g_global.ast = ft_create_ast(g_global.token);
		if (g_global.ast && !g_global.error_type)
		{
			ft_print_ast(g_global.ast, 0);
			ft_start_execution(g_global.ast);
			ft_free_tokens(&g_global.token);
			ft_free_ast(g_global.ast);
		}
		else if (g_global.error_type)
		{
			ft_print_error(g_global.token);
			ft_free_tokens(&g_global.token);
			ft_free_ast(g_global.ast);
		}
		g_global.error_type = E_NONE;
	}
	ft_free_envp(&g_global.envp);
	clear_history();
	return (0);
}

