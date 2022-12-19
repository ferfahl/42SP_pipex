/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:11:19 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 22:59:05 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_error_args(int argc, char *argv[], t_data *p_data)
{
	if (argc != 5)
		error_args("Invalid number of arguments\n\
Needed: input_file cmd1 cmd2 output_file", p_data, 1);
	p_data->index = 0;
	p_data->infile = open(argv[1], O_RDONLY);
	if (p_data->infile == -1)
	{
		error_args(argv[1], p_data, 0);
		p_data->infile = open("/dev/null", O_RDONLY);
	}
	p_data->index++;
	p_data->outfile = open(
			argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p_data->outfile == -1)
		error_args(argv[argc - 1], p_data, 1);
	return (0);
}
