/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 17:19:58 by feralves          #+#    #+#             */
/*   Updated: 2022/11/26 17:20:55 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command(char **possible_paths, char *cmd)
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
			return (temp);
		i++;
	}
	return (NULL); //command not found
}

char	*get_path(char *envp[], char *cmd)
{
	int		i;
	char	**possible_paths;
	char	*right_path;
	
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	possible_paths = ft_split(&envp[i][5], ':');
	right_path = find_command(possible_paths, cmd);
	if (!right_path)
		return (NULL);
	return (right_path);
}
