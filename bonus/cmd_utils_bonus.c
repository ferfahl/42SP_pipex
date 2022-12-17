/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:19:58 by feralves          #+#    #+#             */
/*   Updated: 2022/12/17 20:42:39 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	int	i;

	i = 0;
	pipes->cmd = (char ***)malloc(sizeof (char **) * (pipes->n_cmd));
	if (!pipes->cmd)
		if_error("Malloc error", pipes, 1);
	pipes->path = (char **)malloc(sizeof (char *) * (pipes->n_cmd));
	if (!pipes->path)
		if_error("Malloc error", pipes, 1);
	pipes->check = (int *)malloc(sizeof (int) * (pipes->n_cmd));
	if (!pipes->check)
		if_error("Malloc error", pipes, 1);
	pipes->pippin = (int **)malloc(sizeof (int *) * (pipes->n_cmd));
	if (!pipes->pippin)
		if_error("Malloc error", pipes, 1);
	while (i <= pipes->n_cmd)
	{
		pipes->pippin[i] = (int *)malloc(sizeof (int) * 2);
		if (!pipes->pippin[i])
			if_error("Malloc error", pipes, 1);
		i++;
	}
}

int	check_cmd(int argc, char *argv[], char *envp[], t_data *pipes)
{
	int		index;
	int		args;
	char	*temp;

	args = 2;
	index = 0;
	pipes->n_cmd = argc - 3;
	ft_malloc_pipes(pipes);
	while (index < pipes->n_cmd)
	{
		pipes->check[index] = 0;
		temp = argv[args];
		pipes->cmd[index] = ft_split_pipex(temp);
		pipes->path[index] = get_path(envp, pipes->cmd[index][0]);
		if (pipes->path[index] == NULL)
		{
			ft_putstr_fd(pipes->cmd[index][0], 2);
			if_error(": command not found", pipes, 0);
			pipes->check[index] = -1;
			close(pipes->fd[index]);
			pipes->fd[index] = open("/dev/null", O_RDONLY);
		}
		index++;
		args++;
	}
	return (0);
}
