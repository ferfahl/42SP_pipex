/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:55:40 by feralves          #+#    #+#             */
/*   Updated: 2022/11/23 11:53:14 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
//	char	*file1;
	int		fd;
	int		index;
	char *path = "/usr/bin/cat";
	char *cmd[2] = {"cat", NULL};

	index = 0;
	int	child = fork();
	if (child == 0)
	{
		int exe = execve(path, cmd, envp);
		ft_printf("Error?\n");
		return (exe);
	}
	while (argv[index] && argc < 5)
	{
		fd = open(argv[index], O_RDONLY);
		if (fd == -1)
			perror(argv[index]);
		ft_printf("%s\n", argv[index]);
		index++;
	}
/* 	int status;
	waitpid(child, &status, 0);
	if (WIFEXITED(status)) */
	return (0);

}

