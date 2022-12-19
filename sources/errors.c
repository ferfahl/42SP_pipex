/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feralves <feralves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 22:20:54 by feralves          #+#    #+#             */
/*   Updated: 2022/12/18 22:26:34 by feralves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_args(char *file, t_data *p_data, int n)
{
	ft_putstr_fd("bash: ", 2);
	perror(file);
	if (n == 0)
		return ;
	free (p_data);
	exit (1);
}

void	if_error_quotes(char *message, t_data *p_data)
{
	ft_putendl_fd(message, 2);
	free (p_data->cmd);
	free (p_data->path);
	free (p_data);
	exit (1);
}

void	if_error_silent(t_data *p_data, int n)
{
	if (n == 0)
		return ;
	ft_free_all(p_data);
	exit (n);
}

void	if_error(char *message, t_data *p_data, int n)
{
	ft_putendl_fd(message, 2);
	if (n == 0)
		return ;
	ft_free_all(p_data);
	exit (n);
}
