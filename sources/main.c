/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:37:24 by feralves          #+#    #+#             */
/*   Updated: 2022/11/23 12:14:31 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	if_error(char *message, t_data pipes)
{
	ft_printf("%s\n", message);
	free(t_data);
	exit(1);
}
/* int	main(int argc, char *argv[], char *envp[])
{
	t_data	pipes;
	
	if (argc != 5)
	{
		ft_printf("Wrong number of arguments for pipex\n");
		exit(1);
	}
	pipes = (t_data *)ft_calloc(1, sizeof(t_data));
	if (pipes == NULL)
		if_error("Calloc error", pipes);
} */