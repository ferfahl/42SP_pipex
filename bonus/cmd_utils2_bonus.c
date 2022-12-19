/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:03:32 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 21:48:09 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	ft_expander(char *argument, char previous, char after)
{
	int		index;
	char	value;

	index = 0;
	value = 0;
	while (argument[index])
	{
		if (argument[index] == '\'' || argument[index] == '\"')
		{
			value = argument[index];
			index++;
			while (argument[index] != value)
			{
				if (argument[index] == previous)
					argument[index] = after;
				index++;
			}
		}
		index++;
	}
	return (value);
}

static void	ft_reswitch(char **cmd)
{
	int		pos;
	char	*temp;

	pos = 0;
	while (cmd[pos])
	{
		ft_expander(cmd[pos], TEMP_SPACE, ' ');
		temp = ft_strtrim(cmd[pos], "\'\"");
		free(cmd[pos]);
		cmd[pos] = temp;
		pos++;
	}
}

int	check_quotes(char *argument)
{
	int		index;
	int		counter;
	
	counter = 0;
	index = 0;
	while (argument[index])
	{
		if (argument[index] == '\'' || argument[index] == '\"')
			counter++;
		index++;
	}
	if (counter % 2 != 0)
		return (-1);
	return (0);
}

char	**ft_split_pipex(char *argument)
{
	char	**cmd;

	if (check_quotes(argument))
		return (NULL);
	ft_expander(argument, ' ', TEMP_SPACE);
	cmd = ft_split(argument, ' ');
	ft_reswitch(cmd);
	return (cmd);
}
