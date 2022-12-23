/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:22:13 by feralves          #+#    #+#             */
/*   Updated: 2022/12/23 22:24:00 by feralves         ###   ########.fr       */
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
