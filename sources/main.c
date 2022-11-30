/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/11/29 22:32:37 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	if_error(char *message, t_data pipes)
{
	ft_printf("%s\n", message);
	free(t_data);
	exit(-1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	pipes;
	
	if (check_error_args(argc, argv, &pipes))
		return (1);
	pipes = (t_data *)ft_calloc(1, sizeof(t_data));
	if (pipes == NULL)
		if_error("Calloc error", pipes);
	if (check_cmd(argc, argv, envp, &pipes))
		return ;
	open_args(argc, argv, &pipes);
	pipex_start(&pipes, envp);
	
}