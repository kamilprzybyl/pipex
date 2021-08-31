#include "../inc/pipe.h"

static void	init(t_data *data, char **argv, char **envp, int argc, int infile, int outfile)
{
	data->argv = argv;
	data->envp = envp;
	data->argc = argc;
	data->outfile = outfile;
	data->infile = infile;
}

int	main(int argc, char **argv, char **envp)
{
	int		infile;
	int		outfile;
	t_data	data;

	if (argc < 5)
		return (write(1, "To few arguments\n", 18));
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
		return (1);
	}
	init(&data, argv, envp, argc, infile, outfile);
	pipex(&data);
	close(outfile);
	return (0);
}
