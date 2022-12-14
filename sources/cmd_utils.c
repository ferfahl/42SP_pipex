/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:19:58 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 22:31:26 by feralves         ###   ########.fr       */
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

void	ft_malloc_p_data(t_data *p_data)
{
	p_data->cmd = malloc(sizeof (char **) * 2);
	if (!p_data->cmd)
		if_error("Malloc error", p_data, 1);
	p_data->path = malloc(sizeof (char *) * 2);
	if (!p_data->path)
		if_error("Malloc error", p_data, 1);
}

int	check_cmd(int argc, char *argv[], char *envp[], t_data *p_data)
{
	int		index;

	index = 2;
	ft_malloc_p_data(p_data);
	while (index <= argc - 2)
	{
		p_data->check[index - 2] = 0;
		p_data->cmd[index - 2] = ft_split_pipex(argv[index]);
		if (!p_data->cmd[index - 2])
			if_error_quotes("Error: quotes not closed", p_data);
		p_data->path[index - 2] = get_path(envp, p_data->cmd[index - 2][0]);
		if (p_data->path[index - 2] == NULL)
		{
			ft_putstr_fd(p_data->cmd[index - 2][0], 2);
			if_error(": command not found", p_data, 0);
			p_data->check[index - 2] = -1;
			close(p_data->infile);
			p_data->infile = open("/dev/null", O_RDONLY);
		}
		index++;
	}
	return (0);
}
