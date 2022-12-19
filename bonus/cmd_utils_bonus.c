/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:19:58 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 22:09:33 by feralves         ###   ########.fr       */
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
	if (cmd == NULL)
		return (NULL);
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	possible_paths = ft_split(&envp[i][5], ':');
	right_path = find_command(possible_paths, cmd);
	ft_free_array(possible_paths);
	if (right_path == NULL)
		return (NULL);
	return (right_path);
}

void	check_cmd(int argc, char *argv[], char *envp[], t_data *p_data)
{
	int		index;
	int		args;

	args = 2;
	index = 0;
	p_data->n_cmd = argc - 3;
	ft_malloc_p_data(p_data);
	while (index < p_data->n_cmd)
	{
		p_data->check[index] = 0;
		p_data->cmd[index] = ft_split_pipex(argv[args]);
		if (p_data->cmd[index] == NULL)
			if_error_quotes("Error: quotes not closed", p_data);
		p_data->path[index] = get_path(envp, p_data->cmd[index][0]);
		if (p_data->path[index] == NULL)
		{
			ft_putstr_fd(p_data->cmd[index][0], 2);
			if_error(": command not found", p_data, 0);
			p_data->check[index] = -1;
			close(p_data->infile);
			p_data->infile = open("/dev/null", O_RDONLY);
		}
		index++;
		args++;
	}
}
