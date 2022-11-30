/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:11:19 by feralves          #+#    #+#             */
/*   Updated: 2022/11/29 22:19:20 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_error_args(int argc, char *argv[], t_data pipes)
{
	if (argc != 5)
		if_error("Invalid number of arguments\n
		Needed: input_file cmd1 cmd2 output_file", pipes);
	//check for argv[1] access -> if can't use them give error
	//check for argv[argc - 1] access -> if can't use them give error
}

void	open_args(int argc, char *argv[], t_data *pipes)
{
	pipes->index = 0;
	pipes->fd[pipes->index] = open(argv[1], O_RDONLY);
	if (pipes.fd[pipes->index] == -1)
		if_error("No such file or directory", pipes);
	pipes->index++;
	pipes.fd[pipes->index] = open(argv[argc - 1], O_RDONLY);
	if (pipes.fd[pipes->index] == -1)
	{
		//create new file
		//open new file in pipes.fd[pipes->index]
	}
}
