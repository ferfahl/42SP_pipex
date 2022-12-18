/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:11:19 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 19:10:30 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_error_args(int argc, char *argv[], t_data *pipes)
{
	if (argc < 5)
		error_args("Invalid number of arguments\n\
Needed: input_file cmd1 cmd2 cmd[n] output_file", pipes, 1);
	pipes->index = 0;
	pipes->infile = open(argv[1], O_RDONLY);
	if (pipes->infile == -1)
	{
		error_args(argv[1], pipes, 0);
		pipes->infile = open("/dev/null", O_RDONLY);
	}
	pipes->index++;
	pipes->outfile = open(
			argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (pipes->outfile == -1)
		error_args(argv[argc - 1], pipes, 1);
	return (0);
}
