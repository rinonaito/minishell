#include "minishell.h"

void	ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (src != '\0' && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_search_path(const char *filename)
{
	char	path[PATH_MAX];
	char 	*value;
	char	*duplicated;
	char	*end;

	value = getenv("PATH");
	while (value != NULL)
	{
		ft_bzero(path, PATH_MAX);
		end	= ft_strchr(value, ':');
		if (end != NULL)
			ft_strncpy(path, value, end - value);
		else
			ft_strncpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		duplicated = NULL;
		if (access(path, X_OK) == 0)
		{
			duplicated = ft_strdup(path);
			return (duplicated);
		}
		value = end + 1;
	}
	return (NULL);
}

void	ft_interpret(char *line)
{
	extern char **environ;
	pid_t		child_pid;
	char 		*argv[] = {line, NULL};
	int			wstatus;
	char		*path;

	path = ft_search_path(line);
	child_pid = fork(); //strat a new process
	if (child_pid < 0)
		exit(0);
	if (child_pid == 0) // in child process
		execve(path, argv, environ);
	else // in parent process
		wait(&wstatus);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("\x1b[1;38;5;122mminishell🐣 \033[0m");
		if (line == NULL)
		{
			free (line);
			break;
		}
		if (strlen(line) != 0)
			add_history(line);
		ft_interpret(line);
		free (line);
	}
	return (0);
}
