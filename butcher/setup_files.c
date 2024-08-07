#include "minishell.h"

int	ft_redir_in(char	*file)
{
	int	infile_fd;

	ft_putstr_fd(file, 1);
	infile_fd = open(file, O_RDONLY, 0444);
	if (infile_fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	dup2(infile_fd, 0);
	close(infile_fd);
	return (0);
}

int	ft_redir_out(char	*file)
{
	int	outfile_fd;

	outfile_fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("Error creating outfile\n");
		return (1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	return (0);
}

int	ft_redir_append(char	*file)
{
	int	append_fd;

	append_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (append_fd == -1)
	{
		perror("Error creating outfile\n");
		return (1);
	}
	dup2(append_fd, 1);
	close(append_fd);
	return (0);
}

void	child_get_input(char *delimeter, int pfd[])
{
	char	*line;

	close(pfd[0]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (ft_strncmp(line, delimeter, ft_strlen(delimeter)) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(pfd[1], line, ft_strlen(line));
		free(line);
	}
}

int	get_here_doc(char *delimeter)
{
	int		pfd[2];
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	if (pipe(pfd) == -1)
	{
		perror("Error in pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error when forking");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_get_input(delimeter, pfd);
	else
	{
		wait(&exit_status);
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
	}
	return (exit_status);
}
