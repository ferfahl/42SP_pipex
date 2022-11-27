/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/11/27 20:24:13 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	if_error(char *message, t_data pipes)
{
	ft_printf("%s\n", message);
	free(t_data);
	return (1);
}

int	check_cmd(int argc, char *argv[], char *envp[], t_data pipes)
{
	pipes.index = 2
	while (pipes.index < argc - 2)
	{
		//if ("")
			//temp = ft_strtrim_mod(argc[pipes.index], """");
			//pipes.cmd1 = ft_split(temp, " ");
		//get_path(envp, pipes.cmd1);
		//pipex.index++;

		//COMO PEGAR O CMD2 AQUI?
	}
}

int	check_error_args(int argc, char *argv[], t_data pipes)
{
	if (argc != 5)
		if_error("Invalid number of arguments\n
		Needed: input_file cmd1 cmd2 output_file", pipes);
	//check for argv[1] access -> if can't use them give error
	//check for argv[argc - 1] access -> if can't use them give error
}

void	open_args(int argc, char *argv[], t_data pipes)
{
	pipes.fd1 = open(argv[1], O_RDONLY);
	if (pipes.fd1 == -1)
		if_error("No such file or directory", pipes);
	pipes.fd2 = open(argv[argc - 1], O_RDONLY);
	if (pipes.fd2 == -1)
	{
		//create new file
		//open new file in pipes.fd2
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	pipes;
	
	if (check_error_args(argc, argv, &pipes))
		return (1);
	pipes = (t_data *)ft_calloc(1, sizeof(t_data));
	if (pipes == NULL)
		if_error("Calloc error", pipes);
	if (check_cmd(argc, argv, envp, &pipes))
		return ;
	open_args(argc, argv, &pipes);
	pipex_start(&pipes);
	
}