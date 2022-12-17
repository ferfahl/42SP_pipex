/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/17 20:30:20 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_process(t_data *pipes, int n, int *pippin[], char *envp[])
{
	dup2(pippin[n][0], STDIN);
	dup2(pipes->fd[n], STDOUT);
	close(pippin[n][1]);
	close(pippin[n][0]);
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

void	middle_process(t_data *pipes, int n, int *pippin[], char *envp[])
{
	dup2(pippin[n][1], STDIN);
	dup2(pippin[n][0], STDOUT);
	close(pippin[n][1]);
	close(pippin[n][0]);
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (pipes->check[n] == 0)
	{
		pipes->check[n] = execve(pipes->path[n], pipes->cmd[n], envp);
		if_error("Last process did not work", pipes, 1);
		exit(pipes->check[n]);
	}
	if_error("", pipes, 127);
}

void	first_process(t_data *pipes, int n, int *pippin[], char *envp[])
{
	dup2(pipes->fd[n], STDIN);
	dup2(pippin[n][1], STDOUT);
	close(pippin[n][1]);
	close(pippin[n][0]);
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

void	ft_close_pipes(t_data *pipes, int *pippin[])
{
	int	p;

	p = 0;
	while (p <= pipes->n_cmd)
	{
		close(pippin[p][0]);
		close(pippin[p][1]);
		p++;
	}
	close(pipes->fd[0]);
	close(pipes->fd[1]);
}

void	pipex_start(t_data *pipes, char *envp[])
{
	int		status;
	int		i;
	pid_t	child;

	i = 0;
	while (i <= pipes->n_cmd)
	{
		if (pipe(pipes->pippin[i]))
			if_error("Pipe could not be created", pipes, 1);
		child = fork();
		if (child == 0)
		{
			if (i == 0)
				first_process(pipes, 0, pipes->pippin, envp);
			else if (i == pipes->n_cmd)
				last_process(pipes, 1, pipes->pippin, envp);
			else
				middle_process(pipes, 1, pipes->pippin, envp);
		}
		i++;
	}
	waitpid(child, &status, 0);
	ft_close_pipes(pipes, pipes->pippin);
	if (WIFEXITED(status))
		pipes->status = WEXITSTATUS(status);
	status = pipes->status;
	ft_free_all(pipes);
	exit(status);
}
