/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 14:37:52 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_process(t_data *pipes, int n, char *envp[])
{
	int	i;

	i = 0;
	dup2(pipes->pippin[n - 1][0], STDIN);
	dup2(pipes->fd[1], STDOUT);
	while (i < n)
	{
		close(pipes->pippin[i][1]);
		close(pipes->pippin[i][0]);
		i++;
	}
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

void	middle_process(t_data *pipes, int n, char *envp[])
{
	int	i;

	i = 0;
	dup2(pipes->pippin[n][1], STDOUT);
	dup2(pipes->pippin[n - 1][0], STDIN);
	while (i < n)
	{
		close(pipes->pippin[i][1]);
		close(pipes->pippin[i][0]);
		i++;
	}
	close(pipes->fd[0]);
	close(pipes->fd[1]);
	if (pipes->check[n] == 0)
	{
		pipes->check[n] = execve(pipes->path[n], pipes->cmd[n], envp);
		if_error("Middle process did not work", pipes, 1);
		exit(pipes->check[n]);
	}
	if_error("", pipes, 127);
}

void	first_process(t_data *pipes, int n, char *envp[])
{
	dup2(pipes->fd[0], STDIN);
	dup2(pipes->pippin[n][1], STDOUT);
	close(pipes->pippin[n][1]);
	close(pipes->pippin[n][0]);
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

void	ft_close_pipes(t_data *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->n_cmd)
	{
		close(pipes->pippin[i][0]);
		close(pipes->pippin[i][1]);
		i++;
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
	while (i < pipes->n_cmd)
	{
		if (pipe(pipes->pippin[i]))
			if_error("Pipe could not be created", pipes, 1);
		child = fork();
		if (child == 0)
		{
			if (i == 0)
				first_process(pipes, i, envp);
			else if (i == (pipes->n_cmd - 1))
				last_process(pipes, i, envp);
			else
				middle_process(pipes, i, envp);
		}
		i++;
	}
	ft_close_pipes(pipes);
	while (wait(&status) != -1);
	if (WIFEXITED(status))
		pipes->status = WEXITSTATUS(status);
	status = pipes->status;
	ft_free_all(pipes);
	exit(status);
}
