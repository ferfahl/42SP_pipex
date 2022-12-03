/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/12/03 18:47:43 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	if_error(char *message, t_data *pipes, int n)
{
	ft_printf("%s\n", message);
	if (n == 0)
		return ;
	free (pipes);
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
	if (check_cmd(argc, argv, envp, pipes))
		return (1);
	pipex_start(pipes, envp);
	//falta limpar e liberar tudo pós pipex
}