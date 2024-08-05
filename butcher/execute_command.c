#include "minishell.h"

extern t_global	g_global;

char	*create_path(char *path, char *cmd)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cmd_path);
}

char	*get_path(char *cmd, char **envp)
{
	char	**split_path;
	char	*cmd_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	split_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (split_path[i] != NULL)
	{
		cmd_path = create_path(split_path[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_split(split_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_split(split_path);
	ft_free_ast(g_global.ast);
	ft_free_tokens(&g_global.token);
	return (NULL);
}

void	execute_command(char *command, char **envp)
{
	char	**split_command;
	char	*path;

	if (command == NULL || command[0] == '\0')
		return ;
	if (ft_strchr(command, '\''))
		split_command = ft_handle_quotes(command);
	else
		split_command = ft_split(command, ' ');
    path = get_path(split_command[0], envp);
    if (path == NULL)
    {
        write(2, "command not found: ", 19);
		write(2, split_command[0], ft_strlen(split_command[0]));
		write(2, "\n", 1);
		free_split(split_command);
        exit(EXIT_FAILURE);
    }
	if (execve(path, split_command, envp) == -1)
	{
		write(2, "command not found: ", 19);
		write(2, split_command[0], ft_strlen(split_command[0]));
		write(2, "\n", 1);
		free_split(split_command);
		free(path);
		exit(EXIT_FAILURE);
	}
}
