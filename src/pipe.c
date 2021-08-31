#include "../inc/pipe.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**fetch_paths(t_data *data)
{
	char	*index;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", data->envp[i], 5))
		i++;
	index = ft_strchr(data->envp[i], '=');
	return (ft_split(index + 1, ':'));
}

void	ft_exec(t_data *data, char **cmd_args)
{
	int		i;
	char	*cmd;
	char	**paths;

	i = 0;
	paths = fetch_paths(data);
	while (paths[i])
	{
		if (!cmd_args[0])
			write(2, "zsh: command not found: \n", 26);
		cmd = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = cmd;
		cmd = ft_strjoin(paths[i], cmd_args[0]);
		if (!cmd)
			exit(1);
		execve(cmd, cmd_args, data->envp);
		free(cmd);
		i++;
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putendl_fd(cmd_args[0], 2);
	free_arr(paths);
	free_arr(cmd_args);
	exit(1);
}

void	handle_child(t_data *data, int tmp_fd, int i, int *pipe_fd)
{
	char	**cmd_args;

	cmd_args = ft_split(data->argv[i], ' ');
	dup2(tmp_fd, STDIN_FILENO);
	if (i == data->argc - 2)
		dup2(data->outfile, STDOUT_FILENO);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	ft_exec(data, cmd_args);
}

void	pipex(t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		tmp_fd;
	int		i;

	i = 1;
	tmp_fd = data->infile;
	while (++i < data->argc - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		else if (pid == 0)
			handle_child(data, tmp_fd, i, pipe_fd);
		else
		{
			waitpid(-1, NULL, 0);
			close(pipe_fd[1]);
			close(tmp_fd);
			dup2(pipe_fd[0], tmp_fd);
			close(pipe_fd[0]);
		}
	}
}
