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
	g_global.stdin = dup(0);
	g_global.stdout = dup(1);
}

int	main(int ac, char **av, char **env)
{
	char	*line = NULL;

	(void)ac;
	(void)av;
	g_global.envp = ft_duplicate_envp(env);
	while (1)
	{
		line = readline("My_minishell-> ");
		if (!line)
			continue ;
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		if (line[0])
			add_history(line);
		if (!ft_strncmp(line, "env", 3))
			ft_print_envp(g_global.envp);
		g_global.token = ft_get_tokens(line);
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

