/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 17:12:59 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 22:45:35 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_args(char *file, t_data *pipes, int n)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	if (n == 0)
		return ;
	free (pipes);
	exit (1);
}

void	if_error_silent(t_data *pipes, int n)
{
	if (n == 0)
		return ;
	ft_free_all(pipes);
	exit (n);
}

void	if_error(char *message, t_data *pipes, int n)
{
	ft_putendl_fd(message, 2);
	if (n == 0)
		return ;
	ft_free_all(pipes);
	exit (n);
}
