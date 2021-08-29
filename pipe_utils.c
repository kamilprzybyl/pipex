#include "pipe.h"

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
