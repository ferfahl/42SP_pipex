/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 21:05:14 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_process(t_data *p_data, int n, char *envp[])
{
	int	i;

	i = 0;
	dup2(p_data->pipes[n - 1][0], STDIN);
	dup2(p_data->outfile, STDOUT);
	while (i < n)
	{
		close(p_data->pipes[i][1]);
		close(p_data->pipes[i][0]);
		i++;
	}
	close(p_data->infile);
	close(p_data->outfile);
	if (p_data->check[n] == 0)
	{
		p_data->check[n] = execve(p_data->path[n], p_data->cmd[n], envp);
		if_error("Last process did not work", p_data, 1);
		exit(p_data->check[n]);
	}
	if_error_silent(p_data, 127);
}

void	middle_process(t_data *p_data, int n, char *envp[])
{
	int	i;

	i = 0;
	dup2(p_data->pipes[n][1], STDOUT);
	dup2(p_data->pipes[n - 1][0], STDIN);
	while (i < n)
	{
		close(p_data->pipes[i][1]);
		close(p_data->pipes[i][0]);
		i++;
	}
	close(p_data->infile);
	close(p_data->outfile);
	if (p_data->check[n] == 0)
	{
		p_data->check[n] = execve(p_data->path[n], p_data->cmd[n], envp);
		if_error("Middle process did not work", p_data, 1);
		exit(p_data->check[n]);
	}
	if_error_silent(p_data, 127);
}

void	first_process(t_data *p_data, int n, char *envp[])
{
	dup2(p_data->infile, STDIN);
	dup2(p_data->pipes[n][1], STDOUT);
	close(p_data->pipes[n][1]);
	close(p_data->pipes[n][0]);
	close(p_data->infile);
	close(p_data->outfile);
	if (p_data->check[n] == 0)
	{
		p_data->check[n] = execve(p_data->path[n], p_data->cmd[n], envp);
		if_error("First process did not work", p_data, 1);
		exit(p_data->check[n]);
	}
	if_error_silent(p_data, 127);
}

void	ft_close_p_data(t_data *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->n_cmd)
	{
		close(p_data->pipes[i][0]);
		close(p_data->pipes[i][1]);
		i++;
	}
	close(p_data->infile);
	close(p_data->outfile);
}

void	pipex_start(t_data *p_data, char *envp[]) //too many lines
{
	int		status;
	int		i;
	pid_t	child;

	i = 0;
	while (i < p_data->n_cmd)
	{
		if (pipe(p_data->pipes[i]))
			if_error("Pipe could not be created", p_data, 1);
		child = fork();
		if (child == 0)
		{
			if (i == 0)
				first_process(p_data, i, envp);
			else if (i == (p_data->n_cmd - 1))
				last_process(p_data, i, envp);
			else
				middle_process(p_data, i, envp);
		}
		i++;
	}
	ft_close_p_data(p_data);
	while (wait(&status) != -1);
		//não pode ser assim;
	if (WIFEXITED(status))
		p_data->status = WEXITSTATUS(status);
	status = p_data->status;
	ft_free_all(p_data);
	exit(status);
}
