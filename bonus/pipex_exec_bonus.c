/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 22:12:17 by feralves          #+#    #+#             */
/*   Updated: 2022/12/23 22:26:55 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_which_process(t_data *p_data, int i, char *envp[])
{
	if (i == 0)
		first_process(p_data, i, envp);
	else if (i == (p_data->n_cmd - 1))
		last_process(p_data, i, envp);
	else
		middle_process(p_data, i, envp);
}

void	pipex_start(t_data *p_data, char *envp[])
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
			ft_which_process(p_data, i, envp);
		i++;
	}
	ft_close_p_data(p_data);
	wait(&status);
	if (WIFEXITED(status))
		p_data->status = WEXITSTATUS(status);
	status = p_data->status;
	ft_free_all(p_data);
	exit(status);
}
