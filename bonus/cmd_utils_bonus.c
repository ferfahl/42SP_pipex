/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:19:58 by feralves          #+#    #+#             */
/*   Updated: 2022/12/10 22:42:17 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_command(char **possible_paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*command;

	i = 0;
	command = ft_strjoin("/", cmd);
	while (possible_paths[i])
	{
		temp = ft_strjoin(possible_paths[i], command);
		if (access(temp, F_OK) == 0)
		{
			free(command);
			if (access(temp, X_OK) == 0)
				return (temp);
			else
				return (NULL);
		}
		free(temp);
		i++;
	}
	free(command);
	return (NULL);
}

static char	*get_path(char *envp[], char *cmd)
{
	int		i;
	char	**possible_paths;
	char	*right_path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	possible_paths = ft_split(&envp[i][5], ':');
	right_path = find_command(possible_paths, cmd);
	ft_free_array(possible_paths);
	if (right_path == NULL)
		return (NULL);
	return (right_path);
}

void	ft_malloc_pipes(t_data *pipes)
{
	pipes->cmd = malloc(sizeof (char **) * 2);
	if (!pipes->cmd)
		if_error("Malloc error", pipes, 1);
	pipes->path = malloc(sizeof (char **) * 2);
	if (!pipes->path)
		if_error("Malloc error", pipes, 1);
}

int	check_cmd(int argc, char *argv[], char *envp[], t_data *pipes)
{
	int		index;
	char	*temp;

	index = 2;
	ft_malloc_pipes(pipes);
	while (index <= argc - 2)
	{
		pipes->check[index - 2] = 0;
		temp = argv[index];
		pipes->cmd[index - 2] = ft_split_pipex(temp);
		pipes->path[index - 2] = get_path(envp, pipes->cmd[index - 2][0]);
		if (pipes->path[index - 2] == NULL)
		{
			ft_putstr_fd(pipes->cmd[index - 2][0], 2);
			if_error(": command not found", pipes, 0);
			pipes->check[index - 2] = -1;
			close(pipes->fd[index - 2]);
			pipes->fd[index - 2] = open("/dev/null", O_RDONLY);
		}
		index++;
	}
	return (0);
}
