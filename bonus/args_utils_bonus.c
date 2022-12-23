/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:11:19 by feralves          #+#    #+#             */
/*   Updated: 2022/12/23 22:18:50 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_error_args(int argc, char *argv[], t_data *p_data)
{
	if (argc < 5)
		error_args("Invalid number of arguments\n\
Needed: input_file cmd1 cmd2 cmd[n] output_file", p_data, 1);
	else
		p_data->infile = open(argv[1], O_RDONLY);
	if (p_data->infile == -1)
	{
		error_args(argv[1], p_data, 0);
		p_data->infile = open("/dev/null", O_RDONLY);
	}
	p_data->outfile = open(
			argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p_data->outfile == -1)
		error_args(argv[argc - 1], p_data, 1);
	return (0);
}
