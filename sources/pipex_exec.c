/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/03 19:29:44 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	second_process(t_data *pipes, int fd, int cavalinho[], char *envp[])
{
	int	exe;
	
	close(cavalinho[1]);
	dup2(cavalinho[0], 0);
	dup2(pipes->fd[fd], 1);
	exe = execve(pipes->path[fd], pipes->cmd[fd], envp);
	if_error("Second process did not work", pipes, 1);
	return(exe);
}

int	first_process(t_data *pipes, int fd, int cavalinho[], char *envp[])
{
	int exe;
	
	dup2(pipes->fd[fd], 0);
	dup2(cavalinho[1], 1);
	exe = execve(pipes->path[fd], pipes->cmd[fd], envp);
	if_error("First process did not work", pipes, 1);
	return(exe);
}

void	pipex_start(t_data *pipes, char *envp[])
{
	int	cavalinho[2];
	int	mario;
	int child1;
	int	child2;
	
	mario = pipe(cavalinho);
	if (mario)
		if_error("Pipe could not be created", pipes, 1);
	child1 = fork();
	if (child1 == 0)
		first_process(pipes, 0, cavalinho, envp);
	waitpid(child1, &pipes->status, 0);
	close(pipes->fd[0]);
	child2 = fork();
	if (child2 == 0)
		second_process(pipes, 1, cavalinho, envp);
	waitpid(child2, &pipes->status, 0);
	close(cavalinho[1]);
	close(cavalinho[0]);
}