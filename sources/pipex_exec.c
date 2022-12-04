/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/04 17:09:13 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_process(t_data *pipes, int n, int cavalinho[], char *envp[])
{
	dup2(cavalinho[0], 0);
	dup2(pipes->fd[n], 1);
	close(cavalinho[1]);
	close(cavalinho[0]);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (pipes->check[n] == 0)
	{
		pipes->check[n] = execve(pipes->path[n], pipes->cmd[n], envp);
		if_error("Second process did not work", pipes, 1);
		exit(pipes->check[n]);
	}
	exit(127);
}

void	first_process(t_data *pipes, int n, int cavalinho[], char *envp[])
{
	dup2(pipes->fd[n], 0);
	dup2(cavalinho[1], 1);
	close(cavalinho[1]);
	close(cavalinho[0]);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (pipes->check[n] == 0)
	{
		pipes->check[n] = execve(pipes->path[n], pipes->cmd[n], envp);
		if_error("First process did not work", pipes, 1);
		exit(pipes->check[n]);
	}
	exit(127);
}

void	pipex_start(t_data *pipes, char *envp[])
{
	int	cavalinho[2];
	int child1;
	int	child2;
	
	if (pipe(cavalinho))
		if_error("Pipe could not be created", pipes, 1);
	child1 = fork();
	if (child1 == 0)
		first_process(pipes, 0, cavalinho, envp);
	waitpid(-1, NULL, WNOHANG);
	child2 = fork();
	if (child2 == 0)
		second_process(pipes, 1, cavalinho, envp);
	waitpid(-1, NULL, WNOHANG);
	close(cavalinho[1]);
	close(cavalinho[0]);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
}
