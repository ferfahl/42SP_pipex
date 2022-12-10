/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/10 22:35:10 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_process(t_data *pipes, int n, int pippin[], char *envp[])
{
	dup2(pippin[0], 0);
	dup2(pipes->fd[n], 1);
	close(pippin[1]);
	close(pippin[0]);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (pipes->check[n] == 0)
	{
		pipes->check[n] = execve(pipes->path[n], pipes->cmd[n], envp);
		if_error("Second process did not work", pipes, 1);
		exit(pipes->check[n]);
	}
	if_error("", pipes, 127);
}

void	first_process(t_data *pipes, int n, int pippin[], char *envp[])
{
	dup2(pipes->fd[n], 0);
	dup2(pippin[1], 1);
	close(pippin[1]);
	close(pippin[0]);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (pipes->check[n] == 0)
	{
		pipes->check[n] = execve(pipes->path[n], pipes->cmd[n], envp);
		if_error("First process did not work", pipes, 1);
		exit(pipes->check[n]);
	}
	if_error("", pipes, 127);
}

void	pipex_start(t_data *pipes, char *envp[])
{
	int		pippin[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pippin))
		if_error("Pipe could not be created", pipes, 1);
	child1 = fork();
	if (child1 == 0)
		first_process(pipes, 0, pippin, envp);
	child2 = fork();
	if (child2 == 0)
		second_process(pipes, 1, pippin, envp);
	close(pippin[1]);
	close(pippin[0]);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		pipes->status = WEXITSTATUS(status);
	wait(NULL);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	status = pipes->status;
	ft_free_all(pipes);
	exit(status);
}
