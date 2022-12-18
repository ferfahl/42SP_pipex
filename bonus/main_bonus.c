/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 22:45:50 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_all(t_data *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->n_cmd)
	{
		ft_free_array(pipes->cmd[i]);
		free(pipes->path[i]);
		free(pipes->pippin[i]);
		i++;
	}
	free(pipes->check);
	free(pipes->pippin);
	free(pipes->cmd);
	free(pipes->path);
	free (pipes);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*pipes;

	pipes = (t_data *)ft_calloc(1, sizeof(t_data));
	if (pipes == NULL)
		if_error("Calloc error", pipes, 1);
	if (check_error_args(argc, argv, pipes))
		return (1);
	(void)envp;
	if (check_cmd(argc, argv, envp, pipes))
		return (1);
	pipex_start(pipes, envp);
}
