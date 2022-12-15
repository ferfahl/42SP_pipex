/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/12/11 00:01:23 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_all(t_data *pipes)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		ft_free_array(pipes->cmd[i]);
		free(pipes->path[i]);
		i++;
	}
	free(pipes->cmd);
	free(pipes->path);
	free (pipes);
}

void	if_error(char *message, t_data *pipes, int n)
{
	ft_putendl_fd(message, 2);
	if (n == 0)
		return ;
	ft_free_all(pipes);
	exit (n);
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
