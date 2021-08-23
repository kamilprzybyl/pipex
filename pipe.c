#include "pipe.h"

void	ft_exec(t_data *data, char **cmd_args)
{
	int		i;
	char	*cmd;
	char	**paths;

	i = 0;
	paths = fetch_paths(data);
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = cmd;
		cmd = ft_strjoin(paths[i], cmd_args[0]);
		if (!cmd)
			exit(1);
		execve(cmd, cmd_args, data->envp);
		ft_putstr_fd("zsh: command not found: ", 1);
		ft_putendl_fd(cmd_args[0], 1);
		free(cmd);
		i++;
	}
	free_arr(paths);	
	free_arr(cmd_args);
	exit(1);
}

static void	handle_child(t_data *data, int outfile, int *tmp_fd, int i, int *pipe_fd)
{
	char	**cmd_args;

	cmd_args = ft_split(data->argv[i], ' ');
	dup2(*tmp_fd, STDIN_FILENO);
	if (i < data->argc - 2)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	close(pipe_fd[0]);
	ft_exec(data, cmd_args);
}

static void	init(t_data *data, char **argv, char **envp, int argc)
{
	data->argv = argv;
	data->envp = envp;
	data->argc = argc;
}

static void pipex(t_data *data, int infile, int outfile)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		tmp_fd;
	char	**cmd_args;
	int		i;

	i = 2;
	tmp_fd = infile;
	close(infile);
	while (i < data->argc - 1)
	{
		if (pipe(pipe_fd) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			exit(1);
		else if (pid == 0)
			handle_child(data, outfile, &tmp_fd, i, pipe_fd);
		else
		{
			waitpid(-1, NULL, 0);
			close(pipe_fd[1]);
			tmp_fd = pipe_fd[0];
			i++;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	t_data	data;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		perror(argv[1]);
		return (1);
	}
	outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror(argv[argc - 1]);
		close(infile);
		close(outfile);
		return (1);
	}
	init(&data, argv, envp, argc);
	pipex(&data, infile, outfile);
	return (0);
}
