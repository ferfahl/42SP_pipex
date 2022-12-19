/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 22:22:57 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_process(t_data *p_data, int n, int pipes[], char *envp[])
{
	dup2(pipes[0], 0);
	dup2(p_data->outfile, 1);
	close(pipes[1]);
	close(pipes[0]);
	close(p_data->infile);
	close(p_data->outfile);
	if (p_data->check[n] == 0)
	{
		p_data->check[n] = execve(p_data->path[n], p_data->cmd[n], envp);
		if_error("Second process did not work", p_data, 1);
		exit(p_data->check[n]);
	}
	if_error_silent(p_data, 127);
}

void	first_process(t_data *p_data, int n, int pipes[], char *envp[])
{
	dup2(p_data->infile, 0);
	dup2(pipes[1], 1);
	close(pipes[1]);
	close(pipes[0]);
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

void	pipex_start(t_data *p_data, char *envp[])
{
	int		pipes[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipes))
		if_error("Pipe could not be created", p_data, 1);
	child1 = fork();
	if (child1 == 0)
		first_process(p_data, 0, pipes, envp);
	child2 = fork();
	if (child2 == 0)
		second_process(p_data, 1, pipes, envp);
	close(pipes[1]);
	close(pipes[0]);
	waitpid(child2, &status, 0);
	if (WIFEXITED(status))
		p_data->status = WEXITSTATUS(status);
	wait(NULL);
	close(p_data->infile);
	close(p_data->outfile);
	status = p_data->status;
	ft_free_all(p_data);
	exit(status);
}

